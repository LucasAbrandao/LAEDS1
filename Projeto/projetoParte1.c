/****************

LAED1 - Projeto (Parte I) - Busca por padrão em sequência

Alunos(as):
Lucas Andrade Brandão

Data: 22/05/2023

****************/

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 10

/* ========================================================================= */

typedef int TipoChave;

typedef struct {
    int Chave;
    int Tipo;
    int NumElementos;
    double PontoMedio;
    /* outros componentes */
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
    TipoItem Item;
    TipoApontador Prox;

}   TipoCelula;

typedef struct {
    TipoApontador Primeiro, Ultimo;

} TipoLista;

/* ========================================================================= */

void FLVazia(TipoLista *Lista){
    Lista -> Primeiro = (TipoApontador) malloc(sizeof(TipoCelula));
    Lista -> Ultimo = Lista -> Primeiro;
    Lista -> Primeiro -> Prox = NULL;
}

int Vazia(TipoLista Lista){
    return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista){
    Lista -> Ultimo -> Prox = (TipoApontador) malloc(sizeof(TipoCelula));
    Lista -> Ultimo = Lista -> Ultimo -> Prox;
    Lista -> Ultimo -> Item = x;
    Lista -> Ultimo -> Prox = NULL;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item){ /*  ---   Obs.: o item a ser retirado e  o seguinte ao apontado por  p --- */
    TipoApontador q;
    if (Vazia(*Lista) || p == NULL || p -> Prox == NULL){
        printf(" Erro   Lista vazia ou posicao nao existe\n");
        return;
    }
    q = p -> Prox;
    *Item = q -> Item;
    p -> Prox = q -> Prox;
    if (p -> Prox == NULL) Lista -> Ultimo = p;

    free(q);
}

void Imprime(TipoLista Lista){
    TipoApontador Aux;
    Aux = Lista.Primeiro -> Prox;
    while (Aux->Prox != NULL){
        printf("%d, ", Aux -> Item.Chave);
        Aux = Aux -> Prox;
    }
    printf("%d", Aux->Item.Chave);
    printf("\n");
} 

/* ========================================================================== */



int main(int argc, char *argv[])
{ 

char* fileName = (char*) malloc(200*sizeof(char));

//leitura de arquivo  
    printf("Digite o nome do arquivo: ");
    scanf("%s", fileName);

    FILE *fp;
    fp = fopen(fileName, "r");

    if (!fp){
        printf("erro ao abrir arquivo\n");
        return 1;
    }

//leitura do input
    TipoLista lista;
    FLVazia(&lista);

    int k,;
    fscanf(fp, "%d ", &k);

    TipoLista* vecListas = (TipoLista*) malloc(k*sizeof(TipoLista));

    for (int i=0; i<k;i++){
        TipoLista auxLista;
        FLVazia(&auxLista);
        vecListas[i] = auxLista;
    }

    for (int i=0; i<k;i++){

        TipoItem itemLeitura;
        while (fscanf(fp,"%d",&itemLeitura.Chave) != EOF){

            Insere(itemLeitura,&vecListas[i]);

            if (fgetc(fp) == 10) break;// '\n\ = 10
        }
        
        }

    Imprime(vecListas[0]);
  return 0;
}