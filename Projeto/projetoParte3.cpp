/****************

LAED1 - Projeto (Parte III) - Estimativa do formato da pista

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

// retorna se foi encontrada a sequencia expecificada dentro de uma lista passada como parametro
//  sequencia q precisa ser encontrda 1 3 2 3 1

int buscaDePadrao(TipoLista result, int tamanho, int *padrao, int padraoSize) // retorna a posicao do inicio do padrao + 1 para evitar o 0 de falso e bugar
{
    int posInicioPadrao = 0;
    TipoApontador Aux = result.Primeiro->Prox;

    while (Aux != NULL)
    {

        if (Aux->Item.Tipo == padrao[0])
        {
            TipoApontador auxRetorno = Aux, backup = Aux;
            int verificador = 1;

            auxRetorno = auxRetorno->Prox;
            for (int i = 1; i < 3; i++)
            {
                if (auxRetorno == NULL || auxRetorno->Item.Tipo != padrao[i])
                    break;

                auxRetorno = auxRetorno->Prox;
                verificador++;
            }

            if (verificador == 3){// achou q entrou na pista , agora tem q analisar se tem obstaculo

                TipoApontador obstaculo = auxRetorno;

                //caso sem obstaculo
                if ((obstaculo == NULL) || (obstaculo->Prox == NULL)) break;

                if ((obstaculo->Item.Tipo == padrao[3]) 
                && (obstaculo->Prox->Item.Tipo == padrao[4])) return posInicioPadrao++;                    
            
                // caso com obstaculo 

                while (obstaculo->Item.Tipo != padrao[2] || obstaculo != NULL){
                    

                    obstaculo = obstaculo->Prox;
                    if ((obstaculo == NULL) || (obstaculo->Prox == NULL) || (obstaculo->Prox->Prox == NULL)) break;

                    if ((obstaculo->Item.Tipo == padrao[2]) && (obstaculo->Prox->Item.Tipo == padrao[3]) 
                    && (obstaculo->Prox->Prox->Item.Tipo == padrao[4])){
                       return  -2;
                    } 
                }
            }

            Aux = backup;
        }

        if (Aux == NULL)
            break;

        Aux = Aux->Prox;
        posInicioPadrao++;
    }

    return -1;
}

int calculoPontoMedio(int a, int b) { return (a + b) / 2; }

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

    cor[0] = 0;
    cor[1] = 128;
    cor[2] = 255;

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
                posGeral += repeticao;
            }
        }

        Aux = Aux->Prox;
    }
}

bool porcentagemAceitavelPadrao(TipoLista *listas, int posInicial, int qntListas, int *padrao, int padraoSize)
{

    int qntAceitos = 0;

    for (int i = posInicial; i < qntListas; i++)
    {

        int tamanhoIntervalos;
        TipoApontador Aux;
        Aux = listas[posInicial].Primeiro->Prox;
        for (tamanhoIntervalos = 0; Aux->Prox != NULL; tamanhoIntervalos++)
            Aux = Aux->Prox;

        if (buscaDePadrao(listas[i], tamanhoIntervalos, padrao, padraoSize) >= 0)
            qntAceitos++;
    }

    if (float(qntAceitos) / float(qntListas) >= 0.7) 
        return true; // pode realizar a operacao

    return false; // nao relaiza a operacao
}

int padraoDeCurva(TipoLista *listas, int posInicial, int qntListas, int *padrao, int padraoSize)
{

    for (int i = posInicial; i < qntListas * 2; i++)
    {

        int tamanhoIntervalos = 0;
        TipoApontador Aux;
        Aux = listas[i].Primeiro->Prox;
        for (; Aux->Prox != NULL; tamanhoIntervalos++)
            Aux = Aux->Prox;

        int pos = buscaDePadrao(listas[i], tamanhoIntervalos, padrao, padraoSize);

        if (pos >= 0)
        { // verifica se tem o padrao

            TipoApontador temp = listas[i].Primeiro->Prox;
            for (int j = 0; j <= pos + 1; j++)
            {
                temp = temp->Prox;
            }

            TipoItem aux;
            aux.PontoMedio = temp->Item.PontoMedio;

            Insere(aux, &listas[qntListas * 2]); // salva todos os pontos medios aceitaveis na lista para analise
        }

    }

    // analise de variacao  listas[qntListas * 2] (lista de pontos medios)

    int num1 = 0;
    int num2 = 0;
    TipoApontador Aux;
    Aux = listas[qntListas * 2].Primeiro->Prox;
    if(Aux != NULL)
        num1 = Aux->Item.PontoMedio;
    else{ // padra nao encontrado
        return 4;
    }
    
    Aux = listas[qntListas * 2].Ultimo;
    if(Aux != NULL)
        num2 = Aux->Item.PontoMedio;
    else{ // padra nao encontrado
        return 4;
    }
    
        
    if ((num1 - num2) >= 25)
    { // curva para direita

        return 1;
    }
    else if ((num1 - num2) <= -25)
    { // curva para esquerda

        return 2;
    }
    else
        return 3; // reto
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

    int linhas, numElementos = 0;
    fscanf(fp, "%d ", &linhas);

    // criacao da lista, aloca o dobro para fazer a a lista de segmentos tipados
    TipoLista *vecListas = (TipoLista *)malloc(((linhas * 2) + 1) * sizeof(TipoLista));

    for (int i = 0; i < (linhas * 2) + 1; i++)
    {
        TipoLista auxLista;
        FLVazia(&auxLista);
        vecListas[i] = auxLista;
    }

    // carregamento de dados dentro do arquivo para a a lista
    for (int i = 0; i < linhas; i++)
    {

        fscanf(fp, "%d ", &numElementos);

        for (int j = 0; j < numElementos; j++)
        {
            TipoItem itemLeitura;
            fscanf(fp, "%d", &itemLeitura.Chave);
            Insere(itemLeitura, &vecListas[i]);
        }
    }

    vecListas[0].Primeiro->Item.NumElementos = numElementos;

    int padraoSize = 5;
    int *padrao = (int *)malloc(padraoSize * sizeof(int));
    padrao[0] = 1;
    padrao[1] = 3;
    padrao[2] = 2;
    padrao[3] = 3;
    padrao[4] = 1;

    for (int i = 0; i < linhas; i++)
        mapeamento(vecListas[i], vecListas[i + linhas]);

    for (int i = linhas; i < (linhas * 2); i++)
    {

        int tamanhoIntervalos = 0;
        TipoApontador Aux;
        Aux = vecListas[linhas].Primeiro->Prox;
        for (; Aux->Prox != NULL; tamanhoIntervalos++)
            Aux = Aux->Prox;

    }

    int verificadorObstaculo = 0;
    for(int i = linhas; i < (linhas * 2); i++){

        int tamanhoIntervalos = 0;
        TipoApontador Aux;
        Aux = vecListas[linhas].Primeiro->Prox;
        for (; Aux->Prox != NULL; tamanhoIntervalos++)
            Aux = Aux->Prox;

        if(buscaDePadrao(vecListas[i],tamanhoIntervalos,padrao,padraoSize)== -2){
            verificadorObstaculo = 1;
        }

    }

    if(verificadorObstaculo == 0){
        printf("Resultado: Pista sem impedimento.");
    }
    else{
        printf("Resultado: Pista com impedimento.");
    }
    return 0;
}