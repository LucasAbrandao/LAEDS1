/****************

LAED1 - Projeto (Parte I) - Busca por padrão em sequência

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
void mapeamento(TipoLista Lista, TipoLista result)
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

    int k = 2, numElementos = 0;
    fscanf(fp, "%d ", &numElementos);

    // criacao da lista, sera usada somente o veclista[0]
    TipoLista *vecListas = (TipoLista *)malloc(k * sizeof(TipoLista));

    for (int i = 0; i < k; i++)
    {
        TipoLista auxLista;
        FLVazia(&auxLista);
        vecListas[i] = auxLista;
    }

    // carregamento de dados dentro do arquivo para a a lista
    for (int i = 0; i < k; i++)
    {

        TipoItem itemLeitura;
        while (fscanf(fp, "%d", &itemLeitura.Chave) != EOF)
        {

            Insere(itemLeitura, &vecListas[i]);
            // numElementos++;

            if (fgetc(fp) == 10)
                break; // '\n\ = 10
        }
    }

    vecListas[0].Primeiro->Item.NumElementos = numElementos;

    int padraoSize = 5;
    int *padrao = (int *)malloc(padraoSize * sizeof(int));
    padrao[0] = 1; padrao[1] = 3; padrao[2] = 2; padrao[3] = 3; padrao[4] = 1;

    mapeamento(vecListas[0], vecListas[1]);

    int tamanhoIntervalos = 0;
    TipoApontador Aux;
    Aux = vecListas[1].Primeiro->Prox;
    for (; Aux->Prox != NULL; tamanhoIntervalos++)
    {
        Aux = Aux->Prox;
    }

    if (buscaDePadrao(vecListas[1], tamanhoIntervalos, padrao, padraoSize))
    {
        printf("Resultado: Padrao encontrado.\n");
    }
    else
    {
        printf("Resultado: Padrao nao encontrado.\n");
    }

    return 0;
}