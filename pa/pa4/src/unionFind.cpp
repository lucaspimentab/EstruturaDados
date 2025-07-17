#include "unionFind.hpp"

UnionFind::UnionFind(int quantidade_subconjuntos) {
    tamanho = quantidade_subconjuntos;
    subconjuntos = new Subconjunto[tamanho];
    for (int i = 0; i < tamanho; ++i)
        Make(i);
}

UnionFind::~UnionFind() {
    delete[] subconjuntos;
}

void UnionFind::Make(int x) {
    subconjuntos[x].representante = x;
    subconjuntos[x].rank = 0;
}

int UnionFind::Find(int x) {
    if (subconjuntos[x].representante != x)
        subconjuntos[x].representante = Find(subconjuntos[x].representante);
    return subconjuntos[x].representante;
}

void UnionFind::Union(int x, int y) {
    int xroot = Find(x);
    int yroot = Find(y);
    if (xroot == yroot) return;

    if (subconjuntos[xroot].rank < subconjuntos[yroot].rank) {
        subconjuntos[xroot].representante = yroot;
    } else if (subconjuntos[xroot].rank > subconjuntos[yroot].rank) {
        subconjuntos[yroot].representante = xroot;
    } else {
        subconjuntos[yroot].representante = xroot;
        subconjuntos[xroot].rank++;
    }
}