#ifndef LISTAADJACENCIA_HPP
#define LISTAADJACENCIA_HPP

#include <list>
#include <iostream>

class ListaAdjacencia {
public:
    ListaAdjacencia();
    ~ListaAdjacencia();
    void adicionaVertice();
    void adicionaAresta(int v, int w);
    void imprimeVizinhos(int v);
    int grau(int v);
    int tamanho();
    bool haAresta(int v, int w);
private:
    std::list<int>* lista;
    int numVertices;
};

#endif