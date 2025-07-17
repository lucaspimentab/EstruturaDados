#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP

typedef struct {
    int representante;
    int rank;
} Subconjunto;

class UnionFind {
public:
    UnionFind(int quantidade_subconjuntos);
    ~UnionFind();
    void Make(int x);
    int Find(int x);
    void Union(int x, int y);

private:
    int tamanho;
    Subconjunto* subconjuntos;
};

#endif