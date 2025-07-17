#include <iostream>
#include <vector>
#include <algorithm>
#include "unionFind.hpp"

using namespace std;

struct Aresta {
    int u, v, custo;
};

bool compara(const Aresta& a, const Aresta& b) {
    return a.custo < b.custo;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<Aresta> arestas(m);
    for (int i = 0; i < m; ++i)
        cin >> arestas[i].u >> arestas[i].v >> arestas[i].custo;

    sort(arestas.begin(), arestas.end(), compara);

    UnionFind uf(n);
    int custo_total = 0;

    for (const auto& aresta : arestas) {
        if (uf.Find(aresta.u) != uf.Find(aresta.v)) {
            uf.Union(aresta.u, aresta.v);
            custo_total += aresta.custo;
        }
    }

    cout << custo_total << endl;
    return 0;
}