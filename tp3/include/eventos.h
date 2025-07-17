#ifndef EVENTOS_H
#define EVENTOS_H

#include "estruturas.h"

// Vetor global para armazenar todos os eventos.
// Garante que os ponteiros retornados permaneçam válidos.
extern Evento* eventos[100000];
extern int totalEventos;

// Função para criar um novo evento e armazená-lo no vetor global.
Evento* novoEvento(long datahora, char tipo[], char linha[]);

#endif