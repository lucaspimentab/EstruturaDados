#include "Grafo.hpp"
#include <algorithm>

Grafo::Grafo() {
    vertices = new ListaAdjacencia();
    numVertices = 0;
    numArestas = 0;
}

Grafo::~Grafo() {
    delete vertices;
}

void Grafo::InsereVertice() {
    vertices->adicionaVertice();
    numVertices++;
}

void Grafo::InsereAresta(int v, int w) {
    vertices->adicionaAresta(v, w);
    numArestas++;
}

int Grafo::QuantidadeVertices() {
    return numVertices;
}

int Grafo::QuantidadeArestas() {
    int total = 0;
    for (int i = 0; i < numVertices; ++i)
        total += vertices->grau(i);
    return total / 2;
}

int Grafo::GrauMinimo() {
    int min = vertices->grau(0);
    for (int i = 1; i < numVertices; i++) {
        min = std::min(min, vertices->grau(i));
    }
    return min;
}

int Grafo::GrauMaximo() {
    int max = vertices->grau(0);
    for (int i = 1; i < numVertices; i++) {
        max = std::max(max, vertices->grau(i));
    }
    return max;
}

void Grafo::ImprimeVizinhos(int v) {
    vertices->imprimeVizinhos(v);
}

bool Grafo::Completo() {
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (i != j && !vertices->haAresta(i, j)) {
                return false;
            }
        }
    }
    return true;
}