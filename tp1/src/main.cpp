#include "OrdenadorUniversal.hpp"
#include <cstdio>
#include <cstdlib>
#include <chrono>

int main() {
    long int seed;
    double limiarCusto, a, b, c;
    int tam;

    // Ler parâmetros linha a linha
    if (scanf("%ld", &seed) != 1) {
        fprintf(stderr, "Erro na leitura do seed\n");
        return 1;
    }
    if (scanf("%lf", &limiarCusto) != 1) {
        fprintf(stderr, "Erro na leitura do limiarCusto\n");
        return 1;
    }
    if (scanf("%lf", &a) != 1) {
        fprintf(stderr, "Erro na leitura do coeficiente a\n");
        return 1;
    }
    if (scanf("%lf", &b) != 1) {
        fprintf(stderr, "Erro na leitura do coeficiente b\n");
        return 1;
    }
    if (scanf("%lf", &c) != 1) {
        fprintf(stderr, "Erro na leitura do coeficiente c\n");
        return 1;
    }
    if (scanf("%d", &tam) != 1) {
        fprintf(stderr, "Erro na leitura do tamanho do vetor\n");
        return 1;
    }

    printf("Parâmetros lidos:\nseed=%ld\nlimiarCusto=%.6f\na=%.6f\nb=%.6f\nc=%.6f\ntam=%d\n",
           seed, limiarCusto, a, b, c, tam);

    // Substituir pelos coeficientes calibrados (obtidos da regressão)
    a = 4.5012360849021245e-05;
    b = -1.2345748005851766e-06;
    c = 5.646603832604499e-06;

    printf("Coeficientes calibrados usados:\na=%.10f\nb=%.10f\nc=%.10f\n", a, b, c);

    int* v = new int[tam];
    for (int i = 0; i < tam; ++i) {
        if (scanf("%d", &v[i]) != 1) {
            fprintf(stderr, "Erro na leitura do vetor na posição %d\n", i);
            delete[] v;
            return 1;
        }
    }

    printf("Primeiros 10 valores do vetor: ");
    for (int i = 0; i < (tam < 10 ? tam : 10); ++i) {
        printf("%d ", v[i]);
    }
    printf("\n");

    OrdenadorUniversal ord(v, tam, a, b, c, seed);
    int numQuebras = ord.contaQuebras();
    printf("size %d seed %ld breaks %d\n\n", tam, seed, numQuebras);

    int mps = ord.determinaLimiarParticao(limiarCusto);
    int lq = ord.determinaLimiarQuebras(mps, limiarCusto);

    auto start = std::chrono::high_resolution_clock::now();
    ord.ordenadorUniversal(mps, lq);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    printf("Tempo de execução: %.6f segundos\n", elapsed.count());

    printf("cmp %d move %d calls %d\n", ord.cmp, ord.move, ord.calls);

    delete[] v;
    return 0;
}
