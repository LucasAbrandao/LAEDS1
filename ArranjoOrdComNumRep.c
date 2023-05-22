#include <stdio.h>
#include <malloc.h>

/*
Digite a quantidade de numeros: 10
Digite a sequencia de numeros: 0 0 1 1 1 2 2 3 3 4
*/

int main(){

    int size;
    printf("Digite a quantidade de numeros: ");
    scanf("%d",&size);


    int* vec = (int*)malloc(size*sizeof(int));

    printf("Digite a sequencia de numeros: ");
    for(int i=0; i<size; i++){
        scanf("%d",&vec[i]);
    }

    int cont=0;

    for (int i=0; i < size-cont-1; i++){

        if (vec[i] == vec[i+1]){
            
            for (int j=i+1; j<(size-cont);j++){
                
                vec[j] = vec[j+1];

            }
            cont++;
            i--;

        }
    }
    
    printf("\nResultado: existe(m) %d numero(s) na sequencia final\n",size-cont);
    printf("Sequencia final: ");

    for(int i=0; i<size-cont; i++){
        printf("%d ",vec[i]);
    }
    printf("\n");

    return 0;
}