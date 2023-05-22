#include <stdio.h>

void decomp(int x, int y)
{

    if (x == y)
    {
        printf("%d\n", x);

        if (x != 1)
        {
            decomp(x, y - 1);
        }
        else
            return;
    }
    else
    {

        int complemento = x - y, cont;

        if (complemento == 0)
        {
            return;
        }
        else
        {

            int cont1=0,aux=(y-complemento),verificador=0;

            printf("%d",y);

            if (aux>1){
                cont1=0;
                while ((aux+y)<= x){
                    cont++;
                    if (cont1 == y){
                        printf(" + %d",cont1);
                    }

                }
                 

            }


        }
        return;
    }
}

int main()
{
    int x;

    scanf("%d", &x);

    decomp(x, x);

    return 0;
}