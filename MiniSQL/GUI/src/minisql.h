#ifndef ___MINI_SQL___
#define ___MINI_SQL___

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


#endif