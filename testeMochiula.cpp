#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int weight, value;
};

int main() {
    string filename;
    cout << "Digite o nome do arquivo: ";
    cin >> filename;
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cout << "Erro ao abrir arquivo" << endl;
        return 1;
    }

    int n_mochilas;
    inputFile >> n_mochilas;

    vector<int> capacidades(n_mochilas);
    for (int i = 0; i < n_mochilas; i++) {
        inputFile >> capacidades[i];
    }

    int n_itens;
    inputFile >> n_itens;

    vector<Item> itens(n_itens);
    for (int i = 0; i < n_itens; i++) {
        inputFile >> itens[i].weight >> itens[i].value;
    }

    vector<vector<int>> solucoes(n_mochilas, vector<int>(n_itens));
    for (int i = 0; i < n_itens; i++) {
        for (int j = 0; j < n_mochilas; j++) {
            inputFile >> solucoes[j][i];
        }
    }

    bool solucao_otima = true;

    for (int j = 0; j < n_mochilas; j++) {
        int capacidade_restante = capacidades[j];

        for (int i = 0; i < n_itens; i++) {
            if (solucoes[j][i] == 1) {
                if (itens[i].weight <= capacidade_restante) {
                    capacidade_restante -= itens[i].weight;
                }
                else {
                    solucao_otima = false;
                    break;
                }
            }
        }

        if (capacidade_restante < 0) {
            solucao_otima = false;
            break;
        }
    }

    if (solucao_otima) {
        cout << "Solucao otima." << endl;
    }
    else {
        bool solucao_viavel = true;
        for (int j = 0; j < n_mochilas; j++) {
            int capacidade_restante = capacidades[j];

            for (int i = 0; i < n_itens; i++) {
                if (solucoes[j][i] == 1) {
                    if (itens[i].weight <= capacidade_restante) {
                        capacidade_restante -= itens[i].weight;
                    }
                    else {
                        solucao_viavel = false;
                        break;
                    }
                }
            }

            if (capacidade_restante < 0) {
                solucao_viavel = false;
                break;
            }
        }

        if (solucao_viavel) {
            cout << "Solucao viavel mas nao otima." << endl;
        }
        else {
            cout << "Solucao inviavel." << endl;
        }
    }

    return 0;
}