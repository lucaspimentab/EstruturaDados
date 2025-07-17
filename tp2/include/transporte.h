#ifndef TRANSPORTE_H
#define TRANSPORTE_H

#include "pacote.h"
#include "armazem.h"
#include "escalonador.h"

// Função responsável por processar um evento de transporte:
// remove pacotes da pilha, gera eventos de chegada, rearmazena excedentes,
// e agenda nova tentativa de transporte.
void processar_transporte(Evento e, FilaEventos* fila, Pilha secoes[][1000], Pacote pacotes[], int capacidade, int latencia, int intervalo, int custo_remocao);

#endif // TRANSPORTE_H