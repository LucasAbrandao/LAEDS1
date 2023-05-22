#include <stdio.h>


void imprimirSomas(int n, int max, int *vetor, int tamanho) {
    // Caso base: n e igual a zero
    if (n == 0) {
        // Imprime a decomposicao em somas
        for (int i = 0; i < tamanho-1; i++) {
           printf("%d + ", vetor[i]);
        }
       printf("%d\n", vetor[tamanho-1]);
    } else {
        // Itera pelos numeros maiores ou iguais a max ate11 1
        for (int i = max; i >= 1; i--) {
            // Verifica se e possivel somar i com os numeros anteriores
            if (n >= i) {
                // Adiciona i ao vetor e chama a funcao recursivamente com n-i
                vetor[tamanho] = i;
                imprimirSomas(n-i, i, vetor, tamanho+1);
            }
        }
    }
}

int main() {
    int n;
    printf("Digite um numero inteiro: ");
    scanf("%d", &n);
    printf("Decomposicao:\n");

    int vetor[n]; // Aloca um vetor de tamanho n
    imprimirSomas(n, n, vetor, 0);

    return 0;
}