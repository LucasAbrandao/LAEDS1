#include <iostream>
#include <math.h>

using namespace std;


int mult(int base, int exp){

        if (exp == 0){
            return 1;
        }
        else{
            exp--;
            return base * mult(base,exp);
        }
}


int main(){

    int base,exp;

    cout << "Digite a base e o expoente inteiros: ";
    cin >> base >> exp;

    cout << "Resultado: " << mult(base,exp);

    return 0;
}