#include "../include/escalonador.h"
#include <stdio.h>

// Inicializa a fila de eventos, zerando o tamanho
void inicializa_fila(FilaEventos* f) {
    f->tamanho = 0;
}

// Função que gera a chave de prioridade para o evento
long long gerar_chave_prioridade(Evento e) {
    long long chave = 0;

    if (e.tipo == 1) {
        // Armazenamento (Tipo 1): chave é baseada no tempo (1-6), pacote_id (7-12), e tipo (13)
        chave = e.tempo * 1000000LL + e.pacote_id;  // Tempo * 10^6 + Pacote ID
    } 
    else if (e.tipo == 2) {
        // Transporte (Tipo 2): chave é baseada no tempo (1-6), origem (7-9), destino (10-12), e tipo (13)
        chave = e.tempo * 1000000LL + e.origem * 1000LL + e.destino;  // Tempo * 10^6 + Origem * 10^3 + Destino
    }

    return chave;
}

// Função de comparação para a fila de prioridade
bool evento_menor(Evento a, Evento b) {
    long long chave_a = gerar_chave_prioridade(a);  // Gera a chave de prioridade para 'a'
    long long chave_b = gerar_chave_prioridade(b);  // Gera a chave de prioridade para 'b'

    // Compara as chaves de prioridade
    return chave_a < chave_b;
}

// Insere um evento na fila, mantendo a ordem de prioridade com estabilidade
void inserir_evento(FilaEventos* f, Evento e) {
    int i = f->tamanho - 1;

    // Insere de forma estável: desloca apenas eventos maiores
    while (i >= 0 && evento_menor(e, f->eventos[i])) {
        f->eventos[i + 1] = f->eventos[i];
        i--;
    }

    f->eventos[i + 1] = e;
    f->tamanho++;
}

// Extrai o próximo evento da fila (o de maior prioridade)
Evento extrair_proximo(FilaEventos* f) {
    Evento e = f->eventos[0];

    for (int i = 1; i < f->tamanho; i++) {
        f->eventos[i - 1] = f->eventos[i];
    }

    f->tamanho--;
    return e;
}

// Verifica se a fila de eventos está vazia
bool fila_vazia(FilaEventos* f) {
    return f->tamanho == 0;
}

