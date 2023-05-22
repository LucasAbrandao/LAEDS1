#include <stdio.h>

void imprimirSomas(int n, int max, int *vetor, int tamanho) {
    if (n == 0) {
        for (int i = 0; i < tamanho-1; i++) {
            printf("%d + ", vetor[i]);
        }
        printf("%d\n", vetor[tamanho-1]);
    } else {
        for (int i = max; i >= 1; i--) {
            if (n >= i) {
                vetor[tamanho] = i;
                imprimirSomas(n-i, i, vetor, tamanho+1);
            }
        }
    }
}

int main() {
    int n;
    printf("Digite um número inteiro: ");
    scanf("%d", &n);

    int vetor[n];
    imprimirSomas(n, n, vetor, 0);

    return 0;
}
