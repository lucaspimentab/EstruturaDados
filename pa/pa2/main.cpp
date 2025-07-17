#include "Grafo.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    Grafo g;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        g.InsereVertice();
    }

    for (int i = 0; i < n; ++i) {
        int m, vizinho;
        std::cin >> m;
        for (int j = 0; j < m; ++j) {
            std::cin >> vizinho;
            g.InsereAresta(i, vizinho);
        }
    }

    std::string op = argv[1];
    if (op == "-d") {
        std::cout << g.QuantidadeVertices() << std::endl;
        std::cout << g.QuantidadeArestas() << std::endl;
        std::cout << g.GrauMinimo() << std::endl;
        std::cout << g.GrauMaximo() << std::endl;
    } else if (op == "-n") {
        for (int i = 0; i < g.QuantidadeVertices(); ++i) {
            g.ImprimeVizinhos(i);
        }
    } else if (op == "-k") {
        std::cout << (g.Completo() ? 1 : 0) << std::endl;
    }

    return 0;
}