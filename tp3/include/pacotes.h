#ifndef PACOTES_H
#define PACOTES_H

#include "eventos.h"

// Nó de uma lista encadeada de eventos associados a um pacote
struct EventoNode {
    Evento* evento;       // Ponteiro para o evento real
    EventoNode* prox;     // Próximo evento na lista
};

// Estrutura para representar um pacote na árvore binária
struct Pacote {
    char id[10];           // Identificador do pacote
    EventoNode *primeiroEvento; // Lista de eventos desse pacote
    EventoNode *ultimoEvento;
    Pacote *esq, *dir;     // Subárvores esquerda e direita
};

// Insere um evento em um pacote na árvore binária de pacotes
Pacote* inserirPacote(Pacote* raiz, char id[], Evento *ev);

// Busca um pacote pelo ID na árvore binária
Pacote* buscarPacote(Pacote* raiz, char id[]);

#endif