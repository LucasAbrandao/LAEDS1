#include <iostream>

using namespace std;


int mdc(int a, int b){

    if(b == 0){ 
        return a;
    }
    else{
        
        return mdc(b,a%b);
        
    }
}

int main(){

    int a,b;

    cout << "Digite dois numeros inteiros: ";
    cin >> a >> b;

    cout << "Resultado: " << mdc(a,b);
    return 0;
}