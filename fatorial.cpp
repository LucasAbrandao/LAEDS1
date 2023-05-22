#include <iostream>
#include <vector>

using namespace std;


int main(){ 

    vector<int> result;
    int num;

    cout << "Digite um numero inteiro: ";
    cin >> num;

    int aux = num;

    while ( aux > 0 ){
        if ((aux%10 >= 0) || (aux>9)){

            result.push_back (aux%10);
            aux /= 10;

        }else{
            result.push_back(aux);
            aux /= 10;
        }
    }

    for (size_t i=num-1; i>1; i--){//faz a multiplicacao por todos os numeros de num ate 2
        
        int carry = 0,aux = 0;

        for (size_t j=0; j<result.size();j++){

            aux = (result[j] * i) + carry;
       

            result[j] = aux%10;
            carry = aux/10;
     

        }
        
        while (carry > 9){
            result.push_back (carry%10);
            carry /= 10;
        }
        if (carry != 0){
            result.push_back (carry);
        }

    }

    cout << "Resultado: ";
    //printf vetor
    for (int i=result.size()-1;i>=0; i--){
        
        cout << result[i];
        
    }
        cout << endl;
        
    return 0;
}