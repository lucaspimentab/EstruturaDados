#include "Heap.hpp"
#include <stdexcept>
#include <algorithm>

Heap::Heap(int maxsize) {
    data = new int[maxsize];
    tamanho = 0;
}

Heap::~Heap() {
    delete[] data;
}

void Heap::Inserir(int x) {
    data[tamanho] = x;
    HeapifyPorCima(tamanho);
    tamanho++;
}

int Heap::Remover() {
    if (Vazio()) {
        throw std::runtime_error("Heap vazio!");
    }

    int raiz = data[0];
    data[0] = data[tamanho - 1];
    tamanho--;
    HeapifyPorBaixo(0);
    return raiz;
}

bool Heap::Vazio() {
    return tamanho == 0;
}

int Heap::GetAncestral(int posicao) {
    return (posicao - 1) / 2;
}

int Heap::GetSucessorEsq(int posicao) {
    return 2 * posicao + 1;
}

int Heap::GetSucessorDir(int posicao) {
    return 2 * posicao + 2;
}

void Heap::HeapifyPorCima(int posicao) {
    while (posicao > 0 && data[posicao] < data[GetAncestral(posicao)]) {
        std::swap(data[posicao], data[GetAncestral(posicao)]);
        posicao = GetAncestral(posicao);
    }
}

void Heap::HeapifyPorBaixo(int posicao) {
    int menor = posicao;

    int esq = GetSucessorEsq(posicao);
    int dir = GetSucessorDir(posicao);

    if (esq < tamanho && data[esq] < data[menor]) {
        menor = esq;
    }

    if (dir < tamanho && data[dir] < data[menor]) {
        menor = dir;
    }

    if (menor != posicao) {
        std::swap(data[posicao], data[menor]);
        HeapifyPorBaixo(menor);
    }
}