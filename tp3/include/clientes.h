#ifndef CLIENTES_H
#define CLIENTES_H

// Nó da lista encadeada de pacotes associados a um cliente
struct PacoteCliente {
    char pacoteId[10];      // ID do pacote
    PacoteCliente *prox;    // Próximo pacote na lista
};

// Estrutura que representa um cliente na árvore binária
struct Cliente {
    char nome[30];          // Nome do cliente (chave da árvore)
    PacoteCliente *pacotes; // Lista encadeada de pacotes
    Cliente *esq, *dir;     // Subárvores esquerda e direita
};

// Insere um pacote para o cliente (cria cliente se não existir)
Cliente* inserirCliente(Cliente* raiz, char nome[], char pacoteId[]);

// Busca um cliente pelo nome
Cliente* buscarCliente(Cliente* raiz, char nome[]);

#endif