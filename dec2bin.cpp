#include <iostream>
#include <math.h>

using namespace std;

void dec2bin(int dec){

    
    //cond de parada
        if(dec == 0)
        {
            return;
        }

    else
    {
        dec2bin(dec/2);

    }

    cout << (dec%2);

    return;

}

int main()
{
    int num;

    cout << "Digite um numero inteiro: ";
    cin >> num;
    cout << "Resultado: ";
    
    if (num>0)
    {
        dec2bin(num);
    }
    else
    {
        cout << "0";
    }
    

    return 0;
}