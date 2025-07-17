#include <cstring>
#include "eventos.h"

Evento* eventos[100000];
int totalEventos = 0;

// Cria um novo evento com as informações passadas
// e armazena no vetor global.
Evento* novoEvento(long datahora, char tipo[], char linha[]) {
    Evento* ev = new Evento;
    ev->datahora = datahora;
    strcpy(ev->tipo, tipo);
    strcpy(ev->linhaCompleta, linha);
    eventos[totalEventos++] = ev;
    return ev;
}