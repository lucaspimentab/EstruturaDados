#ifndef SET_HPP
#define SET_HPP

#include <iostream>
#include <string>

class StringSet {
private:
    std::string* tabela;
    int capacidade;
    int tamanho;

    int Hash(const std::string& chave, int tentativa) const;
    void Rehash();

public:
    StringSet(int capacidadeInicial);
    ~StringSet();

    void Inserir(const std::string& chave);
    void Remover(const std::string& chave);
    bool Pertence(const std::string& chave) const;
    void Imprimir() const;

    StringSet* Uniao(const StringSet* outro) const;
    StringSet* Intersecao(const StringSet* outro) const;
    StringSet* DiferencaSimetrica(const StringSet* outro) const;
};

#endif
