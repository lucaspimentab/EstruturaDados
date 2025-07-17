#include <iostream>
#include "Heap.hpp"

int main() {
    int n;
    std::cin >> n;

    Heap heap(n);
    for (int i = 0; i < n; ++i) {
        int valor;
        std::cin >> valor;
        heap.Inserir(valor);
    }

    while (!heap.Vazio()) {
        std::cout << heap.Remover() << " ";
    }
    std::cout << std::endl;

    return 0;
}