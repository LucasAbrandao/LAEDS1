#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int tamanhoVec (int num){


    return (1+num)*num/2;

}


int* lerNumeros(char* nomeArquivo, int* tamanho) {
    FILE* fp;
    int* vetor;
    int i;

    fp = fopen(nomeArquivo, "r");
    
    // Verificar se o arquivo foi aberto corretamente
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    printf("aspas");
    // Obter o tamanho do vetor a ser alocado
    fscanf(fp, "%i ", tamanho);


    vetor = (int*) malloc(tamanhoVec(*tamanho) * sizeof(int));


    for (i = 0; i < tamanhoVec(*tamanho); i++) {
        fscanf(fp, "%d ", &vetor[i]);
    }

    fclose(fp);

    return vetor;
}



int main() {
    int* vetor;
    int tamanho;

    char arquivo[200];

    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s",arquivo);
    vetor = lerNumeros(arquivo, &tamanho);

    // Imprimir os números do vetor
    for (int i = 0; i < tamanhoVec(tamanho); i++) {
        printf("%d ", vetor[i]);
    }

    tamanho = tamanhoVec(tamanho);

    int melhorLinha,melhorCaixa,somaLinha,somaTotal=0,contLinha=1,auxContaCaixa;
    int bigNum;

    for (int i=0; i<tamanho; i+=contLinha){

        somaLinha=0;
        auxContaCaixa=0;

        somaLinha+=vetor[i];
        for (int j=i; j<contLinha-1;j++){


            if(vetor[j]>vetor[j+1]){
                bigNum = j;
            }else bigNum = j+1;

            somaLinha+=vetor[j+1];
            auxContaCaixa++;
        }
        if (somaTotal+vetor[bigNum] > somaTotal){
            
            melhorLinha = contLinha;
            melhorCaixa = auxContaCaixa;
        }

    contLinha++;
        
    }




    printf("Resposta: fileira %d, caixa %d.",melhorLinha,melhorCaixa);


    free(vetor);

    return 0;
}