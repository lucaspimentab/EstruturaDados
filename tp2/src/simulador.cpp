#include "../include/simulador.h"
#include "../include/pacote.h"
#include "../include/armazem.h"
#include "../include/escalonador.h"
#include "../include/roteador.h"
#include "../include/transporte.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <algorithm>

#define MAX_PACOTES 10000
#define MAX_ARMAZENS 1000

Pacote pacotes[MAX_PACOTES];
Pilha secoes[MAX_ARMAZENS][MAX_ARMAZENS];
int adj[MAX_ARMAZENS][MAX_ARMAZENS];
int capacidade, latencia, intervalo, custo_remocao;
int num_armazens, num_pacotes;
FilaEventos fila;

void executar_simulacao(const char* caminho_entrada) {
    std::ifstream entrada(caminho_entrada);
    if (!entrada.is_open()) {
        std::cerr << "Erro ao abrir arquivo de entrada\n";
        return;
    }

    entrada >> capacidade >> latencia >> intervalo >> custo_remocao;
    entrada >> num_armazens;

    for (int i = 0; i < num_armazens; i++)
        for (int j = 0; j < num_armazens; j++)
            entrada >> adj[i][j];

    int tempo_base = 1e9;
    entrada >> num_pacotes;

    int pacotes_entregues = 0;

    for (int i = 0; i < num_pacotes; i++) {
        int tempo;
        std::string tmp;
        entrada >> tempo >> tmp >> pacotes[i].id >> tmp >> pacotes[i].origem >> tmp >> pacotes[i].destino;

        tempo_base = std::min(tempo_base, tempo);

        Pacote* p = &pacotes[i];
        p->id = i;
        p->tempo_chegada = tempo;
        p->estado = 0;
        p->pos_rota = 0;

        calcular_rota(p, p->origem, p->destino);

        if (p->tamanho_rota < 2) continue;

        Evento e;
        e.tempo = tempo;
        e.tipo = 1;
        e.pacote_id = i;
        e.origem = p->rota[0];
        e.destino = p->rota[1];
        inserir_evento(&fila, e);
    }

    for (int i = 0; i < num_armazens; i++)
        for (int j = 0; j < num_armazens; j++)
            inicializa_pilha(&secoes[i][j]);

    for (int i = 0; i < num_armazens; i++)
        for (int j = 0; j < num_armazens; j++)
            if (adj[i][j]) {
                Evento e;
                e.tempo = tempo_base + intervalo;
                e.tipo = 2;
                e.pacote_id = 0;
                e.origem = i;
                e.destino = j;
                inserir_evento(&fila, e);
            }

    // Processa um evento por vez, respeitando a ordenação da fila
    while (!fila_vazia(&fila) && pacotes_entregues < num_pacotes) {
        Evento e = extrair_proximo(&fila);

        if (e.tipo == 1) {
            Pacote* p = &pacotes[e.pacote_id];
            int atual = e.origem;
            int prox = e.destino;

            if (prox == -1) {
                imprimir_evento_entregue(e.tempo, p->id, atual);
                pacotes_entregues++;
            } else {
                empilha(&secoes[atual][prox], p);
                imprimir_evento_armazenado(e.tempo, p->id, atual, prox);
                p->pos_rota++;
            }

        } else if (e.tipo == 2) {
            processar_transporte(e, &fila, secoes, pacotes, capacidade, latencia, intervalo, custo_remocao);
        }
    }

    entrada.close();
}
