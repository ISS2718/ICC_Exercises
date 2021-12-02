#include "minisql.h"

char dados[600][1024];

void destroiComando(comando *cmd){
    for (int i=0; i<cmd->n_select;i++){
        free(cmd->select[i]);
    }
    free(cmd->select);
    for (int i=0; i<cmd->n_from;i++){
        free(cmd->from[i]);
    }
    free(cmd->from);
    for(int i=0; i<cmd->n_from; i++){
        fclose(cmd->arquivos[i]);
    }
    free(cmd->arquivos);
    if(cmd->flag_where){
      for(int i=0; i<cmd->n_where; i++){
          free(cmd->where_termo1[i]);
          free(cmd->where_termo2[i]);
      }
      free(cmd->where_termo1);
      free(cmd->where_termo2);
      free(cmd->str_where);
    }
    
}

void abrirArquivos(comando *cmd){
    cmd->arquivos = malloc(sizeof(FILE *)*cmd->n_from);
    for(int i=0; i<cmd->n_from;i++){
        char nome_arquivo[20] = "dados/";
        strcat(nome_arquivo,cmd->from[i]);
        strcat(nome_arquivo,".tsv");
        cmd->arquivos[i] = fopen(nome_arquivo, "r");
    }
}

FILE * getFile(const comando *cmd, const char *str){
    int pos_arq = 0;
    while(pos_arq<cmd->n_from && strcmp(str, cmd->from[pos_arq])){
        pos_arq++;
    }
    return cmd->arquivos[pos_arq];
}


int fileLen(FILE *fd){
    rewind(fd);
    char linha[1024];
    int cont_linha = 0;
    while(fgets(linha, 1024,fd)){
        cont_linha++;
    }
    return cont_linha;
}

char* getValue(const comando *cmd, const char *str_original, int n_tab, int n_linha){
    int pos_arq = 0;
    char *str = malloc(sizeof(char)*(strlen(str_original)+1));
    strcpy(str,str_original);
    str[strlen(str_original)]='\0';
    str = strtok(str,".");
  char **lista_tabelas = malloc(sizeof(char *)*cmd->n_from);
  for(int i=0;i<cmd->n_from;i++){
    lista_tabelas[i] = malloc(sizeof(char)*(strlen(cmd->from[i])+1));
    strcpy(lista_tabelas[i],cmd->from[i]);
    lista_tabelas[i][strlen(cmd->from[i])]='\0';
  }

    if(lista_tabelas[0][strlen(lista_tabelas[0])-1]=='.' && str[strlen(str)-1] != '.'){
        strcat(str,".");
    }
    while(pos_arq<cmd->n_from && strcmp(str, lista_tabelas[pos_arq])){
        pos_arq++;
    }
    if(str==NULL){
        printf("NULO");
    }else{
        free(str);
    }
    if(n_linha>fileLen(cmd->arquivos[pos_arq])){
        return NULL;
    }
    rewind(cmd->arquivos[pos_arq]);
  for(int i=0;i<cmd->n_from;i++){
    free(lista_tabelas[i]);
  }
  free(lista_tabelas);
    char linha[200];
    char *campo;
    char *c;
    int cont_linha = 0;
    int cont_tab = 0;
    while(fgets(linha, 200, cmd->arquivos[pos_arq])){
        if(cont_linha == n_linha){
            campo = strtok(linha, "\t");
            while(campo != NULL){
                if(cont_tab==n_tab){
                    if(campo[strlen(campo)-1]=='\n'){
                        campo[strlen(campo)-1] = '\0';
                    }
                    c = malloc(sizeof(char)*(strlen(campo)+1));
                    strcpy(c,campo);
                    c[strlen(campo)]='\0';
                    return c;
                    break;
                    break;
                }else{
                    campo = strtok(NULL, "\t");
                    cont_tab++;
                }                
            }
            cont_tab = 0;
        }     
        cont_linha++;   
    }
}


int getNTab(const comando *cmd, char *str){
    int n_tab = 0;
    char *temp = malloc(sizeof(char)*(strlen(str)+1));
    char *temp_original = temp;
    strcpy(temp, str);
    temp[strlen(str)]='\0';
    temp = strtok(temp, ".");
    temp = strtok(NULL, ".");
    char *valor = getValue(cmd,str,n_tab,0);
    while(strcmp(temp, valor)){
        free(valor);
        valor = getValue(cmd,str,n_tab,0);
        n_tab++;
    }
    free(valor);
    if(n_tab){
        n_tab--;
    }
    free(temp_original);
    return n_tab ;
}

void interpretarWhere(comando *cmd){
    if(cmd->flag_where){
        char *temp = cmd->str_where;
        char where[strlen(temp)];
        strcpy(where, temp);
        if(where[strlen(where)-1]=='\n'){
            where[strlen(where)-1] = '\0';
        }
        char *campos[20];
        temp = strtok(where, " ");
        int n_campos =0;
        while(temp!=NULL){
            campos[n_campos] = temp;
            temp = strtok(NULL, " ");
            n_campos++;
        }
        int cont_where = 0;
        cmd->where_termo1 = malloc(sizeof(char *)*n_campos);

        cmd->where_termo2 = malloc(sizeof(char *)*n_campos);
        for(int i = 0; i<n_campos; i+=4){
            cmd->where_termo1[cont_where] = malloc(sizeof(char)*(strlen(campos[i])+1));
            strcpy(cmd->where_termo1[cont_where], campos[i]);
            cmd->where_termo1[cont_where][strlen(campos[i])]='\0';
            
            cmd->where_termo2[cont_where] = malloc(sizeof(char)*(strlen(campos[i+2])+1));
            strcpy(cmd->where_termo2[cont_where], campos[i+2]);
            cmd->where_termo2[cont_where][strlen(campos[i+2])]='\0';
            cont_where++;
        }
        cmd->n_where = cont_where;
    }
}


void results(comando *cmd){
    interpretarWhere(cmd);
    int n_linhas[cmd->n_from];
    FILE *f;
    for(int i=0; i<cmd->n_from; i++){
        f = getFile(cmd,strcat(cmd->from[i],"."));
        n_linhas[i] = fileLen(f);
    }
    int max_linhas = n_linhas[0];
    for(int i=0; i<cmd->n_from; i++){
        if(cmd->flag_where){
            if(max_linhas != 0 && n_linhas[i]<max_linhas){
                max_linhas = n_linhas[i];
            }
        }else{
            if(n_linhas[i]>max_linhas){
                max_linhas = n_linhas[i];
            }
        }   
    }

    for(int i=1; i<max_linhas; i++){
        int flag_imprime_campo = 1;
        if(cmd->flag_where){
            for(int t=0; t<cmd->n_where; t++){
                if(flag_imprime_campo){
                    char *v1 =NULL;
                    char *v2 =NULL;
                    char *v2_original = NULL;
                    if(cmd->where_termo2[t][0] == '\"'){
                        v2 = malloc(sizeof(char)*(strlen(cmd->where_termo2[t])+1));
                        v2_original=v2;
                        strcpy(v2,cmd->where_termo2[t]);
                        v2[strlen(cmd->where_termo2[t])]='\0';
                        v2= strtok(v2, "\"");
                    }else{
                        int n_tab = getNTab(cmd,cmd->where_termo2[t]);
                        v2 = getValue(cmd,cmd->where_termo2[t],n_tab, i);
                    }
                    int n_tab = getNTab(cmd, cmd->where_termo1[t]);
                    char * campo_termo1 = malloc(sizeof(char)*(strlen(cmd->where_termo1[t])+1));
                    strcpy(campo_termo1,cmd->where_termo1[t]);
                    campo_termo1[strlen(cmd->where_termo1[t])]='\0';
                    char *temp = getValue(cmd,campo_termo1,n_tab, i);
                    if(campo_termo1!=NULL){
                        free(campo_termo1);
                    }
                    
                    v1 = malloc(sizeof(char)*(strlen(temp)+1));
                    strcpy(v1,temp);
                    v1[strlen(temp)]='\0';
                    free(temp);
                    if(strcmp(v1,v2)){
                        flag_imprime_campo = 0;
                    }
                    free(v1);
                    if(v2_original!=NULL){
                        free(v2_original);
                    }
                }
            }
        }
        if(flag_imprime_campo){
            for(int j=0; j<cmd->n_select; j++){
                int n_tab = getNTab(cmd, cmd->select[j]);
                char *valor_campo = getValue(cmd,cmd->select[j],n_tab, i);
                printf("%s\t", valor_campo);
                free(valor_campo);              
                if(j==cmd->n_select-1){
                    printf("\n");
                }
            }           
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
            exit(-1);
        }
        strcpy(select,cmd->select[i]);
        select[strlen(cmd->select[i])]='\0';
        char *tabela;
        char *campo;
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
        free(select);
    }
    
}

comando criarComando (char * entrada){
    comando cmd;
    cmd.n_select=0;
    cmd.n_from=0;
    int inicio = 0;
    int flag_from =0;
    cmd.flag_where = 0;
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
            if(strcmp(sub_str, "select") && strcmp(sub_str, "from") && strcmp(sub_str, "where")){
                if(!flag_from){
                    cmd.n_select +=1;
                    if(cmd.n_select==1){
                        cmd.select = malloc(sizeof(char*)*1);
                        cmd.select[0] = malloc(sizeof(char)*(strlen(sub_str)+1));
                        strcpy(cmd.select[0], sub_str);
                        cmd.select[0][strlen(sub_str)] = '\0';
                    }else{
                        cmd.select = realloc(cmd.select, sizeof(char *)*(cmd.n_select));
                        cmd.select[cmd.n_select-1] = malloc(sizeof(char)*(strlen(sub_str)+1));
                        strcpy(cmd.select[cmd.n_select-1], sub_str);
                        cmd.select[cmd.n_select-1][strlen(sub_str)] = '\0';
                    }
                }else{
                    cmd.n_from +=1;
                    if(cmd.n_from==1){
                        cmd.from = malloc(sizeof(char*)*1);
                        cmd.from[0] = malloc(sizeof(char)*(strlen(sub_str)+2));
                        strcpy(cmd.from[0], sub_str);
                        cmd.from[0][strlen(sub_str)] = '\0';
                    }else{
                        cmd.from = realloc(cmd.from, sizeof(char *)*(cmd.n_from));
                        cmd.from[cmd.n_from-1] = malloc(sizeof(char)*(strlen(sub_str)+2));
                        strcpy(cmd.from[cmd.n_from-1], sub_str);
                        cmd.from[cmd.n_from-1][strlen(sub_str)] = '\0';
                    }
                }
            }else{
                if(!strcmp(sub_str, "from")){
                    flag_from=1;
                }else{
                    if(!strcmp(sub_str, "where")){
                        i++;
                        for(int k = 0; k<strlen(entrada)-i; k++){
                            entrada[k] = entrada[i+k];
                        }
                        entrada[strlen(entrada)-i-1] = '\0';
                        cmd.str_where = malloc(sizeof(char)*(strlen(entrada)+1));
                        strcpy(cmd.str_where,entrada);
                        cmd.str_where[strlen(entrada)] = '\0';
                        cmd.flag_where = 1;
                        free(sub_str);
                        break;
                    }
                }
            }
            free(sub_str);
        }
    }
    abrirArquivos(&cmd);
    return cmd;
}


int main(int argc, char *argv[]){
char* entrada;
entrada = malloc(sizeof(char)*TAMANHO_ENTRADA);
if(entrada==NULL){
    exit(-1);
}
fgets(entrada,TAMANHO_ENTRADA,stdin);
comando cmd = criarComando(entrada);
preencherStruct(&cmd);
results(&cmd);
destroiComando(&cmd);
free(entrada);
}