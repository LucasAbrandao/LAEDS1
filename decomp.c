#include <stdio.h>


void decomp (int x, int y){

    if (x == y){
        printf("%d\n",x);
       
        if (x != 1){
        decomp(x, y-1);
        }else return;
    }else{

        int complemento = x-y,cont;

        if (complemento == 0){
            return;
        }else{

            if ((y >= complemento)){
                if ((complemento > 1) ){

                    printf("%d + %d\n",y,complemento);
                    cont=0;

                    while(complemento > 1){

                        printf("%d + %d",y,--complemento);

                        cont++;
                        if (complemento)

                            for(int i=0; i<cont; i++){

                                printf(" + 1");
                            }

                        printf("\n");

                    }
                }else {

                    printf("%d",y);

                    for (int i=0; i < complemento; i++){
                    printf(" + 1");
            
                    }

                    printf("\n");        
                }
            }

            if (y > 1){
            decomp(x,y-1);
            }
        }
    }
    return;
}


int main(){

    int x;

    scanf("%d",&x);

    decomp(x,x);

    return 0;
}