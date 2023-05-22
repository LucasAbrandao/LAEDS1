#include <stdio.h>
#include <stdlib.h>

int retornaMap(int *vec, int num)
{

    for (int i = 0; 1; i++)
    {
        if (vec[i] == num)
        {
            return ++i;
        }
    }
}

void printMatriz(int **mat, int lin, int col)
{

    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < lin; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    //printf("\n");
}


void sort(int vec[], int n) {

    int i, j, min;
    for (i = 0; i < n-1; i++) {

        min = i;
        for (j = i+1; j < n; j++) {
            if (vec[j] < vec[min]) {
                min = j;
            }
        }
        int temp = vec[min];
        vec[min] = vec[i];
        vec[i] = temp;
    }
}


void removeRep(int *vecAux, int tamanhoaux)
{
    // Remove elementos repetidos
    for (int i = 0; i < tamanhoaux; i++)
    {
        for (int j = i + 1; j < tamanhoaux;)
        {
            if (vecAux[j] == vecAux[i])
            {
                for (int k = j; k < tamanhoaux; k++)
                    vecAux[k] = vecAux[k + 1];

                tamanhoaux--;
            }
            else
            {
                j++;
            }
        }
    }
}

int main()
{

    char* fileName = (char*) malloc(200*sizeof(char));
    printf("Digite o nome do arquivo: ");
    scanf("%s", fileName);

    FILE *fp;
    fp = fopen(fileName, "r");

    if (!fp)
    {
        printf("erro ao abrir arquivo\n");
        return 1;
    }

    int tamanhoVec, tamanhoaux;
    fscanf(fp, "%d ", &tamanhoVec);
    tamanhoaux = tamanhoVec;

    int *vec = (int *)malloc(tamanhoVec * (sizeof(int)));   
    int *vecAux = (int *)malloc(tamanhoaux * (sizeof(int)));

    for (int i = 0; i < tamanhoVec; i++)
    {
        fscanf(fp, "%d ", &vec[i]);
        vecAux[i] = vec[i];
    }

    sort(vecAux, tamanhoaux);      // ordena o vetor
    removeRep(vecAux, tamanhoaux); // remove numeros repetidos no vetor

    // analisar tamanho da matrix
    int tamanhoMatriz = 1;
    for (int i = 0; i < tamanhoVec - 1; i++)
    {
        if (vec[i] != vec[i + 1])
        {
            tamanhoMatriz++;
        }
    }

    // alocacao dinamica da matriz
    int **matriz = (int **)malloc(2 * sizeof(int *));
    for (int i = 0; i < 2; i++)
    {
        matriz[i] = (int *)malloc((tamanhoMatriz - 1) * sizeof(int));
    }

    // logica para colocar numeros obtidos na matriz
    int indiceMat = 0;
    for (int i = 0; i < tamanhoVec; i++)
    {

        int repeticoes = 0;

        for (int j = i; (vec[j] == vec[i]) && (j < tamanhoVec); j++)
        {
            repeticoes++;
        }

        matriz[0][indiceMat] = retornaMap(vecAux, vec[i]);
        matriz[1][indiceMat] = repeticoes;
        indiceMat++;
        i += repeticoes - 1;
    }


    printf("Matriz:\n");
    printMatriz(matriz,tamanhoMatriz,2);


    return 0;
}