#include "../include/transporte.h"
#include <cstdio> // para debug com printf

void processar_transporte(Evento e, FilaEventos* fila, Pilha secoes[][1000], Pacote pacotes[],
                          int capacidade, int latencia, int intervalo, int custo_remocao) {
    int origem = e.origem;
    int destino = e.destino;
    int tempo_base = e.tempo;

    Pacote* removidos[100];
    int total_removidos = 0;
    int tempo_remocao = tempo_base;

    // 1. Desempilha todos os pacotes da seção, registrando tempo de remoção individual
    while (secoes[origem][destino].topo >= 0) {
        Pacote* p = desempilha(&secoes[origem][destino]);
        tempo_remocao += custo_remocao;
        removidos[total_removidos] = p;
        imprimir_evento_removido(tempo_remocao, p->id, origem, destino);
        total_removidos++;
    }

    // 1.1. Corrigir a ordem de remoção para mais antigo primeiro
    for (int i = 0; i < total_removidos / 2; i++) {
        Pacote* tmp = removidos[i];
        removidos[i] = removidos[total_removidos - 1 - i];
        removidos[total_removidos - 1 - i] = tmp;
    }

    // 2. Transporta os primeiros 'capacidade' pacotes (mais antigos)
    int qtd_transporte = capacidade < total_removidos ? capacidade : total_removidos;

    // Tempo fixo para transporte de todos os pacotes desse ciclo
    int tempo_transporte = tempo_base + custo_remocao * total_removidos;

    for (int i = 0; i < qtd_transporte; i++) {
        Pacote* p = removidos[i];
        imprimir_evento_transporte(tempo_transporte, p->id, origem, destino);

        Evento chegada;
        chegada.tempo = tempo_transporte + latencia;
        chegada.tipo = 1;
        chegada.pacote_id = p->id;

        if (p->pos_rota + 1 >= p->tamanho_rota) {
            chegada.origem = destino;
            chegada.destino = -1;
        } else {
            chegada.origem = destino;
            chegada.destino = p->rota[p->pos_rota + 1];
        }

        inserir_evento(fila, chegada);
    }

    // 3. Rearmazenar os demais (mais novos)
    for (int i = qtd_transporte; i < total_removidos; i++) {
        Pacote* p = removidos[i];
        empilha(&secoes[origem][destino], p);
        imprimir_evento_rearmazenado(tempo_transporte, p->id, origem, destino);
    }

    // 4. Reagendar próximo transporte
    Evento proximo;
    proximo.tempo = tempo_base + intervalo;
    proximo.tipo = 2;
    proximo.origem = origem;
    proximo.destino = destino;
    proximo.pacote_id = 0;
    inserir_evento(fila, proximo);
}
