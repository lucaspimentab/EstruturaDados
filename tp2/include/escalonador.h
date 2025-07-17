#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include "pacote.h"

struct FilaEventos {
    Evento eventos[1000];
    int tamanho;
};

void inicializa_fila(FilaEventos* f);
void inserir_evento(FilaEventos* f, Evento e);
Evento extrair_proximo(FilaEventos* f);
bool fila_vazia(FilaEventos* f);

#endif
