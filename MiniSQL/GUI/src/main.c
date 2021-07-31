#include <gtk/gtk.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char **select;
    int n_select;
    char **from;
    int n_from;
    char *str_where;
    int n_where;
    int flag_where;
    char **where_termo1;
    char **where_termo2;
    int n_resultados;
    FILE **arquivos; 
} comando;

void destroiComando(comando *cmd);
void abrirArquivos(comando *cmd);
FILE * getFile(const comando *cmd, const char *str);
int fileLen(FILE *fd);
char * getValue(const comando *cmd, const char *str_original, int n_tab, int n_linha);
int getNTab(const comando *cmd, char *str);
void interpretarWhere(comando *cmd);
void results(comando *cmd);
void montarTabelaDados(comando *cmd, FILE *fd, int n_tab);
void imprimeResultados(comando *cmd);
void preencherStruct(comando *cmd);
comando criarComando (char * entrada);

char dados[600][1024];

int main(int argc, char *argv[])
{
    GtkBuilder *builder; 
    GtkWidget *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "./glade/MiniSQL_GUI1.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_Window"));
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();

    return 0;
}

// called when window is closed
G_MODULE_EXPORT void on_mainWindow_destroy()
{
    gtk_main_quit();
}

G_MODULE_EXPORT void on_main_SearchBar_activate (GtkEntry *entry, gpointer user_data) {
    const char *str_GUI_entry = gtk_entry_get_text (entry);
    char *str_CMD_entry = malloc(sizeof(char) * strlen(str_GUI_entry) + 1);
    strcpy(str_CMD_entry, str_GUI_entry);
    str_CMD_entry[strlen(str_GUI_entry)] = '\0';
    printf("%s\n", str_CMD_entry);
    comando cmd = criarComando(str_CMD_entry);
    free(str_CMD_entry);
    printf("criei o comando");
    preencherStruct(&cmd);
    imprimeResultados(&cmd);
    destroiComando(&cmd);
}
 //select Progs.Sigla, Doscentes.Nome from Progs, docentes

void destroiComando(comando *cmd){
    for (int i=0; i<cmd->n_select;i++){
        free(cmd->select[i]);
    }
    free(cmd->select);
    for (int i=0; i<cmd->n_from;i++){
        free(cmd->from[i]);
    }
    free(cmd->from);

    for (int i = 0; i < cmd->n_from; i++) {
        fclose(cmd->arquivos[i]);
    }
    free(cmd->arquivos);
}
void abrirArquivos(comando *cmd){
    cmd->arquivos = malloc(sizeof(FILE *)*cmd->n_from);
    for(int i=0; i<cmd->n_from;i++){
        char nome_arquivo[20] = "dados/";
        if(cmd->from[i]!=NULL){
          strcat(nome_arquivo,cmd->from[i]);
          strcat(nome_arquivo,".tsv");
          cmd->arquivos[i] = fopen(nome_arquivo, "r");
          if(cmd->arquivos[i] == NULL){
              //printf("Nao conseguiu abrir o arquivo %s\n", nome_arquivo);
          }
        }
        
    }
}

void montarTabelaDados(comando *cmd, FILE *fd, int n_tab){
    rewind(fd);
    static int n_linhas_antigo = 0;
    char linha[1024];
    fgets(linha, 1024,fd);
    char *campo;
    int cont = 0;
    int n_linhas=0;
    while(fgets(linha, 1024,fd)){
        campo = strtok(linha, "\t");
        while(campo){
           if(cont==n_tab){
                if(campo[strlen(campo)-1] == '\n'){
                    campo[strlen(campo)-1] = '\0';
                }
                strcat(dados[n_linhas], campo);
                strcat(dados[n_linhas], "\t");
                n_linhas++;
            } 
            campo = strtok(NULL, "\t");
            cont++;
        }
        cont = 0;
    }
    if(n_linhas>n_linhas_antigo){
        n_linhas_antigo = n_linhas;
    }
    cmd->n_resultados = n_linhas_antigo;
}


void imprimeResultados(comando *cmd){
    for(int i =0; i<cmd->n_resultados;i++){
        char *new_str = malloc(sizeof(char)*(strlen(dados[i])+1));
        
        char *new_antigo = new_str;//char new_str[strlen(dados[i])+1];
        new_str = strtok(dados[i], "\n");
        //strcpy(dados[i], new_str);
        new_str[strlen(dados[i])]='\0';
        while (new_str != NULL) { 
            new_str = strtok(NULL, "\n");
            if(new_str != NULL) {
                dados[i][strlen(dados[i])-1] = '\0';
                strcat(dados[i], new_str);
            }
        }
        free(new_antigo);
    }
    for(int i =0; i<cmd->n_resultados;i++){
        printf("%s\n", dados[i]);
    }
}

void preencherStruct(comando *cmd){
    char primeira_linha[cmd->n_from][1024];
    for(int i = 0; i<cmd->n_from; i++){
        fgets(primeira_linha[i], 1024,cmd->arquivos[i]);
    }

    for(int i=0; i<cmd->n_select; i++){
        char * select = malloc(sizeof(char)*(strlen(cmd->select[i])+1));
        if(select == NULL){
            //printf("Nao conseguiu alocar string.");
            exit(-1);
        }
        strcpy(select,cmd->select[i]);
        select[strlen(cmd->select[i])] = '\0';
        char *tabela;
        char *campo;
        //printf("%s\n", select);
        tabela = strtok(select, ".");
        campo = strtok(NULL, ".");
        int n_arquivo = 0;
        for(int j=0; j<cmd->n_from;j++){
            if(!strcmp(tabela, cmd->from[j])){
                n_arquivo = j;
            }
        }
        int n_tab = 0;
        int inicio = 0;
        char amostra_campo[20];
        strcpy(amostra_campo, "\0");
        for(int t = 0; t<strlen(primeira_linha[n_arquivo]); t++){
            if(primeira_linha[n_arquivo][t] == '\t' || primeira_linha[n_arquivo][t] == '\n'){
                for(int z = inicio; z<t; z++){
                    amostra_campo[z-inicio] = primeira_linha[n_arquivo][z];
                }
                amostra_campo[t-inicio] = '\0';
                inicio = t+1;
                if(strcmp(amostra_campo, campo)){
                    n_tab++;
                }else{
                    break;
                }
                strcpy(amostra_campo, "\0");
            }    
        }
        montarTabelaDados(cmd,cmd->arquivos[n_arquivo],n_tab);
        free(select);
    }
    
}

comando criarComando (char * entrada){
    comando cmd;
    cmd.n_select=0;
    cmd.n_from=0;
    int inicio = 0;
    int flag_from =0;
    for(int i = 0; i<strlen(entrada); i++){
        if(entrada[i]==' ' || i==(strlen(entrada)-1)){
            char *sub_str = malloc(sizeof(char)*(i-inicio+1));
            for(int t=inicio; t<i; t++){
                sub_str[t-inicio] = entrada[t];
            }
            if(sub_str[i-inicio-1]==','){
                sub_str[i-inicio-1]='\0';
            }else{
                sub_str[i-inicio]='\0';
            }
            inicio=i+1;       
            if(strcmp(sub_str, "select") && strcmp(sub_str, "from")){
                if(!flag_from){//select
                    cmd.n_select +=1;
                    if(cmd.n_select==1){
                        cmd.select = malloc(sizeof(char*)*1);
                        cmd.select[0] = malloc(sizeof(char)*(strlen(sub_str)+1));
                        strcpy(cmd.select[0], sub_str);
                        cmd.select[0][strlen(sub_str)]='\0';
                    }else{
                        cmd.select = realloc(cmd.select, sizeof(char *)*(cmd.n_select));
                        cmd.select[cmd.n_select-1] = malloc(sizeof(char)*(strlen(sub_str)+1));
                        strcpy(cmd.select[cmd.n_select-1], sub_str);
                        cmd.select[cmd.n_select-1][strlen(sub_str)]='\0';

                    }
                }else{//from
                    cmd.n_from +=1;
                    if(cmd.n_from==1){
                        cmd.from = malloc(sizeof(char*)*1);
                        cmd.from[0] = malloc(sizeof(char)*(strlen(sub_str)+1));
                        strcpy(cmd.from[0], sub_str);
                        cmd.from[0][strlen(sub_str)] = '\0';
                    }else{
                        cmd.from = realloc(cmd.from, sizeof(char *)*(cmd.n_from));
                        cmd.from[cmd.n_from-1] = malloc(sizeof(char)*(strlen(sub_str)+1));
                        strcpy(cmd.from[cmd.n_from-1], sub_str);
                        cmd.from[cmd.n_from-1][strlen(sub_str)]='\0';
                    }
                }
            }else{
                if(!strcmp(sub_str, "from")){
                    flag_from=1;
                }
            }
            free(sub_str);
        }
    }
    abrirArquivos(&cmd);
    return cmd;
}
