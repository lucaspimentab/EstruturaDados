#include <cstring>
#include "clientes.h"

// Insere um cliente na árvore (ou adiciona um pacote se já existir)
Cliente* inserirCliente(Cliente* raiz, char nome[], char pacoteId[]) {
    if (!raiz) {
        raiz = new Cliente;
        strcpy(raiz->nome, nome);
        raiz->pacotes = new PacoteCliente;
        strcpy(raiz->pacotes->pacoteId, pacoteId);
        raiz->pacotes->prox = nullptr;
        raiz->esq = raiz->dir = nullptr;
    } else if (strcmp(nome, raiz->nome) < 0) {
        raiz->esq = inserirCliente(raiz->esq, nome, pacoteId);
    } else if (strcmp(nome, raiz->nome) > 0) {
        raiz->dir = inserirCliente(raiz->dir, nome, pacoteId);
    } else {
        // Cliente já existe, adiciona pacote se ainda não estiver associado
        PacoteCliente* atual = raiz->pacotes;
        while (atual) {
            if (strcmp(atual->pacoteId, pacoteId) == 0)
                return raiz; // já está
            atual = atual->prox;
        }
        PacoteCliente* novo = new PacoteCliente;
        strcpy(novo->pacoteId, pacoteId);
        novo->prox = raiz->pacotes;
        raiz->pacotes = novo;
    }
    return raiz;
}

// Busca um cliente pelo nome
Cliente* buscarCliente(Cliente* raiz, char nome[]) {
    if (!raiz) return nullptr;
    int cmp = strcmp(nome, raiz->nome);
    if (cmp == 0) return raiz;
    return (cmp < 0) ? buscarCliente(raiz->esq, nome) : buscarCliente(raiz->dir, nome);
}