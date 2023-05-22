#include <iostream>
#include <vector>

using namespace std;

int main() {
    int num;

    cout << "Digite um numero inteiro: ";
    cin >> num;

    vector<int> result; // vetor para armazenar o resultado

    result.push_back(1); // inicializa o resultado com 1

    for (int i = 2; i <= num; i++) { // percorre todos os numeros de 2 até num
        int carry = 0;
        for (int j = 0; j < result.size(); j++) { // multiplica o vetor de resultado por i
            int aux = result[j] * i + carry;
            result[j] = aux % 10; // armazena o digito menos significativo
            carry = aux / 10; // armazena o digito mais significativo
        }
        while (carry != 0) { // adiciona os digitos restantes ao vetor de resultado
            result.push_back(carry % 10);
            carry /= 10;
        }
    }

    cout << "Resultado: ";
    for (int i = result.size() - 1; i >= 0; i--) { // imprime o vetor de resultado
        cout << result[i];
    }
    cout << endl;

    return 0;
}
