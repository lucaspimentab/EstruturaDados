#include "../include/armazem.h"

void inicializa_pilha(Pilha* p) {
    p->topo = -1;
}

void empilha(Pilha* p, Pacote* pacote) {
    if (p->topo < 99) {
        p->pacotes[++(p->topo)] = pacote;
    }
}

Pacote* desempilha(Pilha* p) {
    if (p->topo >= 0) return p->pacotes[(p->topo)--];
    return nullptr;
}

Pacote* topo(Pilha* p) {
    if (p->topo >= 0) return p->pacotes[p->topo];
    return nullptr;
}
