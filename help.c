#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


int tamanhoVec (int num){
    return (1+num)*num/2;
}

int* createVec(char* arquivo, int* tamanho) {
    FILE* fp;
    fp = fopen(arquivo, "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    fscanf(fp, "%i ", tamanho);
    *tamanho = tamanhoVec(*tamanho);
    int* vetor = (int*) malloc(*tamanho+1 * sizeof(int));

    for (int i = 0; i < *tamanho; i++) {
        fscanf(fp, "%d ", &vetor[i]);
    }


    return vetor;
}

int qunatidadeLinhas(int num) {
    int cont = 0;
    int soma = 0;

    while(soma < num) {
        soma += cont;
        cont ++;
    }

    return (cont -1);
}

int main(){

    int tamanho;

    char arquivo[200];

    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s",arquivo);

    int* vetor = createVec(arquivo, &tamanho);

    int num_linhas = qunatidadeLinhas(tamanho);

    int melhorLinha = 1, melhorColuna = 1, somaTotal = vetor[0], somaLinha = vetor[0];

    int maiorSoma = vetor[0];

    int quantidadeLida = 1;

    for(int linha = 2; linha <= num_linhas; linha++) {

        for(int atual = quantidadeLida; atual < quantidadeLida + linha; atual ++) {

            if(somaTotal + vetor[atual] > maiorSoma ) {

                maiorSoma = somaTotal + vetor[atual];
                melhorColuna = atual - quantidadeLida + 1;
                melhorLinha = linha;
            }
            somaLinha += vetor[atual];
        }

        quantidadeLida += linha;

        somaTotal = somaLinha;
    }

    printf("Resposta: fileira %d, caixa %d.",melhorLinha,melhorColuna);

    return 0;
}