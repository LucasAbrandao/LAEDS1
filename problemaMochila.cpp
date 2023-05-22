#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

struct Item
{
    int peso;
    int valor;
};

Item constructorItem(int peso, int valor)
{
    Item item = {peso, valor};

    return item;
}



void melhorCasoFunc(vector<int> capacidades, vector<Item> itens, int pesoMochilaTeste, int valorTeste){
    int num_itens = itens.size();
    int max_valor = -1;
    int pesoMelhorCaso = 0;
    int valorMelhorCaso = 0;
    for (int i = 0; i < pow(2, num_itens); i++) {
        int peso_total = 0;
        int valor_total = 0;
        for (int j = 0; j < num_itens; j++) {
            if (i & (1 << j)) {
                peso_total += itens[j].peso;
                valor_total += itens[j].valor;
            }
        }
        if (peso_total <= pesoMochilaTeste && valor_total > max_valor) {
            max_valor = valor_total;
            pesoMelhorCaso = peso_total;
            valorMelhorCaso = max_valor;
        }
    }

    if (valorMelhorCaso == valorTeste && pesoMelhorCaso == pesoMochilaTeste) {
        cout << "Solucao otima." << endl;
    }
    else {
        cout << "Solucao viavel mas nao otima." << endl;
    }

    // cout << "Melhor valor: " << valorMelhorCaso << endl;
    // cout << "Peso do melhor valor: " << pesoMelhorCaso << endl;
}


int main() {

    FILE *fp;
    char file_name[100];
    cout << "Digite o nome do arquivo: ";
    cin >> file_name;

    fp = fopen(file_name, "r");

    // Verificar se o arquivo foi aberto corretamente
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    vector<int> capacidades;
    vector<Item> itens;

    int qnt_mochilas;
    fscanf(fp, "%d", &qnt_mochilas);

    for (int i = 0, aux; i < qnt_mochilas; i++) {
        fscanf(fp, "%d", &aux);
        capacidades.push_back(aux);
    }

    int num_itens;
    fscanf(fp, "%d", &num_itens);

    for (int i = 0, peso, valor; i < num_itens; i++) {
        fscanf(fp, "%d %d", &peso, &valor);
        itens.push_back(constructorItem(peso, valor));
    }

    vector<int> entradasTeste;

    for (int i = 0; i < num_itens; i++) {
        for (int j = 0, aux; j < qnt_mochilas; j++) {
            fscanf(fp, "%d", &aux);
            entradasTeste.push_back(aux);
        }
    }

    // caso que precisa ser analisado:
    int valorTeste = 0;
    vector<int> capacidadesTeste(capacidades.size(), 0);

    int contadorItem = 0; // posicoes das mochilas e itens
    for (int i = 0; i < num_itens; i++) {
        for (int j = 0; j < qnt_mochilas; j++, contadorItem++) {
            if (entradasTeste[contadorItem] == 1) {
                capacidadesTeste[j] += itens[i].peso;
                valorTeste += itens[i].valor;
            }
        }
    }

    int pesoMochilaTeste = 0;
    for (vector<int>::size_type i = 0; i < capacidadesTeste.size(); i++) {
    pesoMochilaTeste += capacidadesTeste[i];
}

    melhorCasoFunc (capacidades ,itens,pesoMochilaTeste, valorTeste);

    // printf("Valor Total: %d\n", valorTeste);
    // printf("Peso Total das Mochilas: %d\n", pesoMochilaTeste);

    fclose(fp);

    return 0;
}
