#include "../include/roteador.h"
#include <iostream>

#define MAX_ARMAZENS 1000
extern int adj[MAX_ARMAZENS][MAX_ARMAZENS];
extern int num_armazens;

void calcular_rota(Pacote* pacote, int origem, int destino) {
    int fila[MAX_ARMAZENS], frente = 0, tras = 0;
    int visitado[MAX_ARMAZENS] = {0};
    int anterior[MAX_ARMAZENS];

    for (int i = 0; i < MAX_ARMAZENS; i++) anterior[i] = -1;

    fila[tras++] = origem;
    visitado[origem] = 1;

    bool encontrou = false;

    while (frente < tras && !encontrou) {
        int atual = fila[frente++];
        for (int vizinho = 0; vizinho < num_armazens; vizinho++) {
            if (adj[atual][vizinho] && !visitado[vizinho]) {
                fila[tras++] = vizinho;
                visitado[vizinho] = 1;
                anterior[vizinho] = atual;
                if (vizinho == destino) {
                    encontrou = true;
                    break; // encerra o for
                }
            }
        }
    }

    if (!visitado[destino]) {
        std::cerr << "Erro: sem caminho de " << origem << " para " << destino << std::endl;
        pacote->tamanho_rota = 0;
        return;
    }

    int caminho[MAX_ARMAZENS], tamanho = 0;
    for (int v = destino; v != -1; v = anterior[v])
        caminho[tamanho++] = v;

    for (int i = 0; i < tamanho; i++)
        pacote->rota[i] = caminho[tamanho - i - 1];

    pacote->tamanho_rota = tamanho;
}
