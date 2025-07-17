#include "ListaAdjacencia.hpp"

ListaAdjacencia::ListaAdjacencia() {
    lista = nullptr;
    numVertices = 0;
}

ListaAdjacencia::~ListaAdjacencia() {
    delete[] lista;
}

void ListaAdjacencia::adicionaVertice() {
    std::list<int>* novaLista = new std::list<int>[numVertices + 1];
    for (int i = 0; i < numVertices; ++i) {
        novaLista[i] = lista[i];
    }
    delete[] lista;
    lista = novaLista;
    numVertices++;
}

void ListaAdjacencia::adicionaAresta(int v, int w) {
    lista[v].push_back(w);
}

void ListaAdjacencia::imprimeVizinhos(int v) {
    for (int w : lista[v]) {
        std::cout << w << " ";
    }
    std::cout << std::endl;
}

int ListaAdjacencia::grau(int v) {
    return lista[v].size();
}

int ListaAdjacencia::tamanho() {
    return numVertices;
}

bool ListaAdjacencia::haAresta(int v, int w) {
    for (int viz : lista[v]) {
        if (viz == w) return true;
    }
    return false;
}