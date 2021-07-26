#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_ENTRADA 300

char dados[600][1024];

typedef struct{
    char **select;
    char **from;
    int n_select;
    int n_from;
    FILE **arquivos; 
    //char **resultados;
    int n_resultados;
} comando;

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
        strcat(nome_arquivo,cmd->from[i]);
        strcat(nome_arquivo,".tsv");
        cmd->arquivos[i] = fopen(nome_arquivo, "r");
        if(cmd->arquivos[i] == NULL){
            //printf("Nao conseguiu abrir o arquivo %s\n", nome_arquivo);
        }
    }
}

void montarTabelaDados(comando *cmd, FILE *fd, int n_tab){
    rewind(fd);
    static int n_linhas_antigo = 0;
    int i = 0;
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
        char *new_str;
        new_str = strtok(dados[i], "\n");
        strcpy(dados[i], new_str);
        while (new_str != NULL) { 
        new_str = strtok(NULL, "\n");
        if(new_str != NULL) {
            dados[i][strlen(dados[i])-1] = '\0';
            strcat(dados[i], new_str);
        }
    }
        //removerParagrafo(dados[i]);
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
        char * select = malloc(sizeof(char)*strlen(cmd->select[i]));
        if(select == NULL){
            //printf("Nao conseguiu alocar string.");
            exit(-1);
        }
        strcpy(select,cmd->select[i]);
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
                        cmd.select[0] = malloc(sizeof(char)*strlen(sub_str));
                        strcpy(cmd.select[0], sub_str);
                    }else{
                        cmd.select = realloc(cmd.select, sizeof(char *)*(cmd.n_select));
                        cmd.select[cmd.n_select-1] = malloc(sizeof(char)*strlen(sub_str));
                        strcpy(cmd.select[cmd.n_select-1], sub_str);
                    }
                }else{//from
                    cmd.n_from +=1;
                    if(cmd.n_from==1){
                        cmd.from = malloc(sizeof(char*)*1);
                        cmd.from[0] = malloc(sizeof(char)*strlen(sub_str));
                        strcpy(cmd.from[0], sub_str);
                    }else{
                        cmd.from = realloc(cmd.from, sizeof(char *)*(cmd.n_from));
                        cmd.from[cmd.n_from-1] = malloc(sizeof(char)*strlen(sub_str));
                        strcpy(cmd.from[cmd.n_from-1], sub_str);
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

int main(int argc, char *argv[]){
char * entrada;
entrada = malloc(sizeof(char)*TAMANHO_ENTRADA);
if(entrada==NULL) {
    //printf("Nao conseguiu alocar.\n");
    exit(-1);
}
fgets(entrada,TAMANHO_ENTRADA,stdin);
comando cmd = criarComando(entrada);
free(entrada);
preencherStruct(&cmd);
imprimeResultados(&cmd);
destroiComando(&cmd);
}