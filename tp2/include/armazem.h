#ifndef ARMAZEM_H
#define ARMAZEM_H

#include "pacote.h"

struct Pilha {
    Pacote* pacotes[100];
    int topo;
};

void inicializa_pilha(Pilha* p);
void empilha(Pilha* p, Pacote* pacote);
Pacote* desempilha(Pilha* p);
Pacote* topo(Pilha* p);

#endif
