#include <cstring>
#include "pacotes.h"

// Insere um evento em um pacote.
// Se o pacote não existir na árvore, cria o nó do pacote.
// Se o pacote já existir, adiciona o evento ao final da lista de eventos do pacote.
Pacote* inserirPacote(Pacote* raiz, char id[], Evento *ev) {
    if (!raiz) {
        // Pacote não encontrado: cria novo nó
        raiz = new Pacote;
        strcpy(raiz->id, id);
        EventoNode* node = new EventoNode{ev, nullptr};
        raiz->primeiroEvento = raiz->ultimoEvento = node;
        raiz->esq = raiz->dir = nullptr;
    } else if (strcmp(id, raiz->id) < 0) {
        // Insere na subárvore esquerda
        raiz->esq = inserirPacote(raiz->esq, id, ev);
    } else if (strcmp(id, raiz->id) > 0) {
        // Insere na subárvore direita
        raiz->dir = inserirPacote(raiz->dir, id, ev);
    } else {
        // Pacote já existe: adiciona evento ao fim da lista
        EventoNode* node = new EventoNode{ev, nullptr};
        raiz->ultimoEvento->prox = node;
        raiz->ultimoEvento = node;
    }
    return raiz;
}

// Busca um pacote pelo ID na árvore binária.
// Retorna o ponteiro para o nó do pacote ou nullptr se não existir.
Pacote* buscarPacote(Pacote* raiz, char id[]) {
    if (!raiz) return nullptr;
    int cmp = strcmp(id, raiz->id);
    if (cmp == 0) return raiz;
    return (cmp < 0) ? buscarPacote(raiz->esq, id) : buscarPacote(raiz->dir, id);
}