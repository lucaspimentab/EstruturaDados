#ifndef ORDENADOR_UNIVERSAL_HPP
#define ORDENADOR_UNIVERSAL_HPP

#include <string>

class OrdenadorUniversal {
public:
    OrdenadorUniversal(int* vetor, int tamanho, double a_, double b_, double c_, long int seed_);

    int determinaLimiarParticao(double limiarCusto);
    int determinaLimiarQuebras(int limiarParticao, double limiarCusto);
    int contaQuebras();
    void ordenadorUniversal(int minTamParticao, int limiarQuebras);

    void registraEstatisticas(int lq, int cmp_, int move_, int calls_, double custo_);
    std::string imprimeEstatisticas(int lq) const;
    std::string montaEstatistica(int lq) const;
    
    int* v;
    int n;
    int cmp, move, calls;
    double a, b, c;
    long int seed;

private:


    int estatCmp[10000];
    int estatMove[10000];
    int estatCalls[10000];
    double estatCusto[10000];

    void resetaEstatisticas();
    double calculaCusto() const;
    void insercao(int l, int r);
    int mediana(int a, int b, int c);
    void particao(int l, int r, int* i, int* j);
    void quicksort(int l, int r, int minTamParticao);
    int menorCusto(double custos[], int num);

    void calculaNovaFaixa(int& minMPS, int& maxMPS, int& passoMPS, int limParticao, int numMPS, const int mpsVals[]);
    void calculaNovaFaixaQuebras(int& minLQ, int& maxLQ, int melhorIdx, int numLQ, const int lqVals[]);
};

#endif
