/****************

LAED1 - Projeto (Parte II) - Estimativa do formato da pista

Alunos(as):
Lucas Andrade Brandão
Caio Cézar Miranda Carvalho

Data: 23/05/2023

****************/

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 10

/* ========================================================================= */

typedef int TipoChave;

typedef struct
{
    int Chave;
    int Tipo;
    int NumElementos;
    int PontoMedio;
    /* outros componentes */
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula
{
    TipoItem Item;
    TipoApontador Prox;

} TipoCelula;

typedef struct
{
    TipoApontador Primeiro, Ultimo;

} TipoLista;

/* ========================================================================= */

void FLVazia(TipoLista *Lista)
{
    Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

int Vazia(TipoLista Lista)
{
    return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista)
{
    Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = x;
    Lista->Ultimo->Prox = NULL;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{ /*  ---   Obs.: o item a ser retirado e  o seguinte ao apontado por  p --- */
    TipoApontador q;
    if (Vazia(*Lista) || p == NULL || p->Prox == NULL)
    {
        printf(" Erro   Lista vazia ou posicao nao existe\n");
        return;
    }
    q = p->Prox;
    *Item = q->Item;
    p->Prox = q->Prox;
    if (p->Prox == NULL)
        Lista->Ultimo = p;

    free(q);
}

void Imprime(TipoLista Lista)
{
    TipoApontador Aux;
    Aux = Lista.Primeiro->Prox;
    while (Aux->Prox != NULL)
    {
        printf("%d, ", Aux->Item.Chave);
        Aux = Aux->Prox;
    }
    printf("%d", Aux->Item.Chave);
    printf("\n");
}

/* ========================================================================== */

// func parte 1
// retorna se foi encontrada a sequencia expecificada dentro de uma lista passada como parametro
//  sequencia q precisa ser encontrda 1 3 2 3 1

bool buscaDePadrao(TipoLista result, int tamanho, int *padrao, int padraoSize)
{
    TipoApontador Aux = result.Primeiro->Prox;

    while (Aux != NULL)
    {

        if (Aux->Item.Tipo == padrao[0])
        {
            TipoApontador auxRetorno = Aux, backup = Aux;
            int verificador = 1;

            auxRetorno = auxRetorno->Prox;
            for (int i = 1; i < padraoSize; i++)
            {
                if (auxRetorno == NULL || auxRetorno->Item.Tipo != padrao[i])
                    break;

                auxRetorno = auxRetorno->Prox;
                verificador++;
            }

            if (verificador == padraoSize)
                return true;

            Aux = backup;
        }

        if (Aux == NULL)
            break;
        Aux = Aux->Prox;
    }

    return false;
}

int calculoPontoMedio(int a, int b)
{
    return (a + b) / 2;
}

int qntRepeticao(TipoApontador aux)
{

    int num = aux->Item.Chave;

    int i;

    for (i = 0; aux != NULL; i++)
    {

        if (num != aux->Item.Chave)
            break;

        aux = aux->Prox;
    }

    return i;
}

/*
255 (branco) -> 3

1 3 2 3 1
0 255 128 255 0
*/
void    mapeamento(TipoLista Lista, TipoLista result)
{
    int repeticao, posGeral = 0;
    TipoApontador Aux;
    Aux = Lista.Primeiro->Prox;

    int *cor = (int *)malloc(3 * sizeof(int));

    cor[0] = 0; cor[1] = 128; cor[2] = 255;

    while (Aux != NULL)
    {
        posGeral++;

        for (int i = 0; i < 3; i++)
        {

            if (cor[i] == Aux->Item.Chave)
            {

                repeticao = qntRepeticao(Aux);
                for (int i = 0; i < repeticao - 1; i++)
                {
                    Aux = Aux->Prox;
                }

                TipoItem auxItem;
                auxItem.Tipo = i + 1;
                auxItem.PontoMedio = calculoPontoMedio(posGeral, (posGeral + repeticao));
                auxItem.NumElementos = repeticao;
                Insere(auxItem, &result);
            }
        }

        Aux = Aux->Prox;
    }
}

void imprimeTipo(TipoLista Lista)
{
    TipoApontador Aux;
    Aux = Lista.Primeiro->Prox;
    while (Aux->Prox != NULL)
    {
        printf("%d, ", Aux->Item.Tipo);
        Aux = Aux->Prox;
    }
    printf("%d", Aux->Item.Tipo);
    printf("\n");
}

void imprimePontoMedio(TipoLista Lista)
{
    TipoApontador Aux;
    Aux = Lista.Primeiro->Prox;
    while (Aux->Prox != NULL)
    {
        printf("%d, ", Aux->Item.PontoMedio);
        Aux = Aux->Prox;
    }
    printf("%d", Aux->Item.PontoMedio);
    printf("\n");
}

int main(int argc, char *argv[])
{

    char *fileName = (char *)malloc(200 * sizeof(char));

    // leitura de arquivo
    printf("Digite o nome do arquivo: ");
    scanf("%s", fileName);

    FILE *fp;
    fp = fopen(fileName, "r");

    if (!fp)
    {
        printf("erro ao abrir arquivo\n");
        return 1;
    }

    // leitura do input
    TipoLista lista;
    FLVazia(&lista);

    int linhas = 2, numElementos = 0;
    fscanf(fp, "%d ", &linhas);
    

    // criacao da lista, aloca o dobro para fazer a a lista de segmentos tipados 
    TipoLista *vecListas = (TipoLista *)malloc(((linhas * 2)+ 1) * sizeof(TipoLista));

    for (int i = 0; i < linhas; i++)
    {
        TipoLista auxLista;
        FLVazia(&auxLista);
        vecListas[i] = auxLista;
    }

    // carregamento de dados dentro do arquivo para a a lista
    for (int i = 0; i < linhas; i++)
    {

        fscanf(fp, "%d ", &numElementos);

        for (int j=0;j<numElementos;j++){
            TipoItem itemLeitura;
            fscanf(fp, "%d", &itemLeitura.Chave);
            Insere(itemLeitura, &vecListas[i]);
        }

    }

    vecListas[0].Primeiro->Item.NumElementos = numElementos;

    int padraoSize = 5;
    int *padrao = (int *)malloc(padraoSize * sizeof(int));
    padrao[0] = 1; padrao[1] = 3; padrao[2] = 2; padrao[3] = 3; padrao[4] = 1;


    for(int i=0;i<linhas;i++){

        mapeamento(vecListas[i], vecListas[i+linhas]);

    }

    int tamanhoIntervalos = 0;
    TipoApontador Aux;
    Aux = vecListas[1].Primeiro->Prox;
    for (; Aux->Prox != NULL; tamanhoIntervalos++)
    {
        Aux = Aux->Prox;
    }

    TipoApontador aux;
    for (int i=0; aux->Prox != NULL;i++){

        if (!i) printf("\n");

        imprimePontoMedio(vecListas[i+linhas]);
    }

   // buscaDePadrao(vecListas[1], tamanhoIntervalos, padrao, padraoSize)
  

    return 0;
}