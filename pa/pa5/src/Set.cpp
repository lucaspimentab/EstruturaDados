#include "../include/Set.hpp"
#include <iostream>

using namespace std;

StringSet::StringSet(int capacidadeInicial)
    : capacidade(capacidadeInicial), tamanho(0) {
    tabela = new string[capacidade];
    for (int i = 0; i < capacidade; ++i)
        tabela[i] = "";
}

StringSet::~StringSet() {
    delete[] tabela;
}

int StringSet::Hash(const string& chave, int tentativa) const {
    unsigned int h = 0;
    for (char c : chave)
        h = 31 * h + c;
    return (h + tentativa) % capacidade;
}

void StringSet::Rehash() {
    int novaCapacidade = capacidade * 2;
    string* novaTabela = new string[novaCapacidade];
    for (int i = 0; i < novaCapacidade; ++i)
        novaTabela[i] = "";

    for (int i = 0; i < capacidade; ++i) {
        if (tabela[i] != "" && tabela[i] != "#REMOVED#") {
            int tentativa = 0;
            int pos;
            do {
                unsigned int h = 0;
                for (char c : tabela[i])
                    h = 31 * h + c;
                pos = (h + tentativa) % novaCapacidade;
                tentativa++;
            } while (novaTabela[pos] != "");
            novaTabela[pos] = tabela[i];
        }
    }

    delete[] tabela;
    tabela = novaTabela;
    capacidade = novaCapacidade;
}

void StringSet::Inserir(const string& chave) {
    if (Pertence(chave))
        return;

    if ((double)tamanho / capacidade >= 0.75)
        Rehash();

    int tentativa = 0;
    int pos;
    do {
        pos = Hash(chave, tentativa++);
    } while (tabela[pos] != "" && tabela[pos] != "#REMOVED#");

    tabela[pos] = chave;
    tamanho++;
}

void StringSet::Remover(const string& chave) {
    int tentativa = 0;
    int pos;
    do {
        pos = Hash(chave, tentativa++);
        if (tabela[pos] == chave) {
            tabela[pos] = "#REMOVED#";
            tamanho--;
            return;
        }
    } while (tabela[pos] != "" && tentativa < capacidade);
}

bool StringSet::Pertence(const string& chave) const {
    int tentativa = 0;
    int pos;
    do {
        pos = Hash(chave, tentativa++);
        if (tabela[pos] == chave)
            return true;
    } while (tabela[pos] != "" && tentativa < capacidade);
    return false;
}

void StringSet::Imprimir() const {
    for (int i = 0; i < capacidade; ++i)
        if (tabela[i] != "" && tabela[i] != "#REMOVED#")
            cout << tabela[i] << " ";
    cout << endl;
}

StringSet* StringSet::Uniao(const StringSet* outro) const {
    StringSet* resultado = new StringSet(capacidade + outro->capacidade);
    for (int i = 0; i < capacidade; ++i)
        if (tabela[i] != "" && tabela[i] != "#REMOVED#")
            resultado->Inserir(tabela[i]);

    for (int i = 0; i < outro->capacidade; ++i)
        if (outro->tabela[i] != "" && outro->tabela[i] != "#REMOVED#")
            resultado->Inserir(outro->tabela[i]);

    return resultado;
}

StringSet* StringSet::Intersecao(const StringSet* outro) const {
    StringSet* resultado = new StringSet(capacidade);
    for (int i = 0; i < capacidade; ++i)
        if (tabela[i] != "" && tabela[i] != "#REMOVED#" && outro->Pertence(tabela[i]))
            resultado->Inserir(tabela[i]);
    return resultado;
}

StringSet* StringSet::DiferencaSimetrica(const StringSet* outro) const {
    StringSet* resultado = new StringSet(capacidade + outro->capacidade);
    for (int i = 0; i < capacidade; ++i)
        if (tabela[i] != "" && tabela[i] != "#REMOVED#" && !outro->Pertence(tabela[i]))
            resultado->Inserir(tabela[i]);

    for (int i = 0; i < outro->capacidade; ++i)
        if (outro->tabela[i] != "" && outro->tabela[i] != "#REMOVED#" && !Pertence(outro->tabela[i]))
            resultado->Inserir(outro->tabela[i]);

    return resultado;
}