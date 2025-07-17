#ifndef GRAFO_HPP
#define GRAFO_HPP

#include "ListaAdjacencia.hpp"

class Grafo {
public:
    Grafo();
    ~Grafo();
    void InsereVertice();
    void InsereAresta(int v, int w);
    int QuantidadeVertices();
    int QuantidadeArestas();
    int GrauMinimo();
    int GrauMaximo();
    void ImprimeVizinhos(int v);
    bool Completo();
private:
    ListaAdjacencia* vertices;
    int numVertices;
    int numArestas;

};

#endif
