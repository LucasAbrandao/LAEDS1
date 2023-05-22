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
    int n = itens.size();
    int m = capacidades.size();

    // Inicializa a tabela de programação dinâmica
    vector<vector<int>> tabela(n+1, vector<int>(pesoMochilaTeste+1, 0));

    // Preenche a tabela de programação dinâmica
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= pesoMochilaTeste; j++) {
            if (itens[i-1].peso > j) {
                tabela[i][j] = tabela[i-1][j];
            }
            else {
                tabela[i][j] = max(tabela[i-1][j], tabela[i-1][j-itens[i-1].peso] + itens[i-1].valor);
            }
        }
    }

    // Verifica se a solução encontrada é ótima
    bool solucaoOtima = true;
    for (int i = 0; i < m; i++) {
        if (tabela[n][capacidades[i]] != valorTeste) {
            solucaoOtima = false;
            break;
        }
    }

    if (solucaoOtima) {
        cout << "Solucao otima." << endl;
    }
    else {
        cout << "Solucao viavel mas nao otima." << endl;
    }
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
    for (int i = 0; i < capacidadesTeste.size(); i++) {
        pesoMochilaTeste += capacidadesTeste[i];
    }

    melhorCasoFunc (capacidades ,itens,pesoMochilaTeste, valorTeste);

    // printf("Valor Total: %d\n", valorTeste);
    // printf("Peso Total das Mochilas: %d\n", pesoMochilaTeste);

    fclose(fp);

    return 0;
}
