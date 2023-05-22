#include <iostream>

using namespace std;

int Digitos(int N)
{

    int algs=0;

    //condicao de parada
    if ((N%10 == 0) && (N < 10))
    {
        return 0;
    }

    algs++;
    N /= 10;

    if (Digitos(N))
    {
        algs += Digitos(N);
    }

    return algs;
}


int main()
{

    int N=0,result=0;

    cout << "Digite um numero inteiro: ";
    
    cin >> N;

    result = Digitos(N);

    cout << "Resultado: " << result;

    return 0;
}