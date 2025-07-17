#include "OrdenadorUniversal.hpp"
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <string>
#include <iostream>



OrdenadorUniversal::OrdenadorUniversal(int* vetor, int tamanho, double a_, double b_, double c_, long int seed_)
    : v(vetor), n(tamanho), cmp(0), move(0), calls(0), a(a_), b(b_), c(c_), seed(seed_) {}


#include <sstream>
#include <iomanip>

std::string OrdenadorUniversal::montaEstatistica(int lq) const {
    return imprimeEstatisticas(lq);
}

void OrdenadorUniversal::registraEstatisticas(int lq, int cmp_, int move_, int calls_, double custo_) {
    int idx = (lq >= 0) ? lq : -lq + 5000;  // índice positivo para quicksort e negativo para inserção, com deslocamento
    estatCmp[idx] = cmp_;
    estatMove[idx] = move_;
    estatCalls[idx] = calls_;
    estatCusto[idx] = custo_;
}

std::string OrdenadorUniversal::imprimeEstatisticas(int lq) const {
    int idx = (lq >= 0) ? lq : -lq + 5000;
    std::ostringstream oss;
    oss << (lq >= 0 ? "lq " : "in lq ") << std::abs(lq)
        << " cost " << std::fixed << std::setprecision(9) << estatCusto[idx]
        << " cmp " << estatCmp[idx]
        << " move " << estatMove[idx]
        << " calls " << estatCalls[idx]
        << "\n";
    return oss.str();
}

void OrdenadorUniversal::resetaEstatisticas() {
    cmp = move = calls = 0;
}

double OrdenadorUniversal::calculaCusto() const {
    return a * cmp + b * move + c * calls;
}

void OrdenadorUniversal::insercao(int l, int r) {
    calls++;
    for (int i = l + 1; i <= r; i++) {
        cmp++;
        int aux = v[i];
        move++;
        int j = i - 1;

        while (j >= l && aux < v[j]) {
            cmp++;
            v[j + 1] = v[j];
            move++;
            j--;
        }
        v[j + 1] = aux;
        move++;
    }
}

int OrdenadorUniversal::mediana(int a, int b, int c) {
    if ((a <= b) && (b <= c)) return b;
    if ((a <= c) && (c <= b)) return c;
    if ((b <= a) && (a <= c)) return a;
    if ((b <= c) && (c <= a)) return c;
    if ((c <= a) && (a <= b)) return a;
    return b;
}

void OrdenadorUniversal::particao(int l, int r, int* i, int* j) {
    calls++;
    *i = l;
    *j = r;
    int mid = l + (r - l) / 2;
    int x = mediana(v[l], v[mid], v[r]);
    int w;
    do {
        while (v[*i] < x) {
            cmp++;
            (*i)++;
        }
        while (v[*j] > x) {
            cmp++;
            (*j)--;
        }
        cmp++;
        if (*i <= *j) {
            w = v[*i];
            v[*i] = v[*j];
            v[*j] = w;
            move += 3;
            (*i)++;
            (*j)--;
        }
        cmp++;
    } while (*i <= *j);
}

void OrdenadorUniversal::quicksort(int l, int r, int minTamParticao) {
    if (l >= r) return;
    calls++;

    int i, j;
    particao(l, r, &i, &j);

    if (abs(j - l) >= minTamParticao)
        quicksort(l, j, minTamParticao);
    else if (l < j)
        insercao(l, j);

    if (abs(r - i) >= minTamParticao)
        quicksort(i, r, minTamParticao);
    else if (i < r)
        insercao(i, r);
}

int OrdenadorUniversal::contaQuebras() {
    int q = 0;
    for (int i = 1; i < n; ++i)
        if (v[i] < v[i - 1]) q++;
    return q;
}

void OrdenadorUniversal::ordenadorUniversal(int minTamParticao, int limiarQuebras) {
    int q = contaQuebras();
    if (q < limiarQuebras) {
        insercao(0, n - 1);
    } else {
        if (n > minTamParticao)
            quicksort(0, n - 1, minTamParticao);
        else
            insercao(0, n - 1);
    }
}




int shuffleVector(int* vet, int size, int numShuffle) {
    int p1 = 0, p2 = 0, temp;
    for (int t = 0; t < numShuffle; t++) {
        // Gera dois índices distintos
        while (p1 == p2) {
            p1 = (int)(drand48() * size);
            p2 = (int)(drand48() * size);
        }
        // Troca os valores
        temp = vet[p1];
        vet[p1] = vet[p2];
        vet[p2] = temp;

        p1 = p2 = 0;
    }
    return 0;
}



 
int OrdenadorUniversal::menorCusto(double custos[], int num) {
    int melhor = 0;
    for (int i = 1; i < num; ++i)
        if (custos[i] < custos[melhor]) melhor = i;
    return melhor;
}


void OrdenadorUniversal::calculaNovaFaixa(int& minMPS, int& maxMPS, int& passoMPS, int limParticao, int numMPS, const int mpsVals[]) {
    int newMin, newMax;

    if (limParticao == 0) {
        newMin = 0;
        newMax = 2;
    } else if (limParticao == numMPS - 1) {
        newMin = std::max(0, numMPS - 3);
        newMax = numMPS - 1;
    } else {
        newMin = limParticao - 1;
        newMax = limParticao + 1;
    }

    // Proteção contra índices inválidos
    newMin = std::max(0, std::min(newMin, numMPS - 1));
    newMax = std::max(0, std::min(newMax, numMPS - 1));

    minMPS = mpsVals[newMin];
    maxMPS = mpsVals[newMax];
    passoMPS = (maxMPS - minMPS) / 5;
    if (passoMPS == 0) passoMPS++;
}

void OrdenadorUniversal::calculaNovaFaixaQuebras(int& minLQ, int& maxLQ, int melhorIdx, int numLQ, const int lqVals[]) {
    int newMinIdx, newMaxIdx;

    if (melhorIdx == 0) {
        // Melhor valor no limite inferior, avança faixa para direita
        newMinIdx = 0;
        newMaxIdx = std::min(4, numLQ - 1);
    } else if (melhorIdx >= numLQ - 1) {
        // Melhor valor no limite superior, recua faixa para esquerda
        newMaxIdx = numLQ - 1;
        newMinIdx = std::max(0, newMaxIdx - 4);
    } else {
        // Faixa centralizada no melhor índice encontrado
        newMinIdx = std::max(0, melhorIdx - 2);
        newMaxIdx = std::min(numLQ - 1, melhorIdx + 2);
    }

    // Atualiza os limites da faixa de busca para as próximas iterações
    minLQ = lqVals[newMinIdx];
    maxLQ = lqVals[newMaxIdx];
}



void ordenaPorInsercao(int* v, int n) {
    for (int i = 1; i < n; ++i) {
        int chave = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > chave) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}


#include <set>  // necessário para std::set
int OrdenadorUniversal::determinaLimiarParticao(double limiarCusto) {
    static int base[10000], temp[10000];
    std::memcpy(base, v, n * sizeof(int));

    int minMPS = 2, maxMPS = n;
    int passoMPS = std::max(1, (maxMPS - minMPS) / 5);
    int melhorValor = minMPS;

    int iter = 0;
    const int maxIter = 10;
    float mpsDiff = limiarCusto + 1;

    // Função auxiliar para evitar MPS duplicados na mesma iteração
    auto jaInserido = [](int mps, int* mpsVals, int tamanho) -> bool {
        for (int i = 0; i < tamanho; ++i) {
            if (mpsVals[i] == mps) return true;
        }
        return false;
    };

    while (iter < maxIter && mpsDiff > limiarCusto) {
        printf("iter %d\n", iter);

        double custosOrig[100];
        int mpsOrig[100], cmpOrig[100], movOrig[100], callsOrig[100];
        int idxOrig = 0;

        // Estratégia adaptativa
        if ((maxMPS - minMPS) <= 10) {
            for (int mps = minMPS; mps <= maxMPS; ++mps) {
                if (!jaInserido(mps, mpsOrig, idxOrig)) {
                    mpsOrig[idxOrig++] = mps;
                }
            }
        } else {
            for (int mps = minMPS; mps <= maxMPS; mps += passoMPS) {
                if (!jaInserido(mps, mpsOrig, idxOrig)) {
                    mpsOrig[idxOrig++] = mps;
                }
            }

            // Só adiciona maxMPS se ele não foi o último do passo
            if (idxOrig < 6 && !jaInserido(maxMPS, mpsOrig, idxOrig)) {
                mpsOrig[idxOrig++] = maxMPS;
                
            }
        
        }

        // Executa os testes
        for (int i = 0; i < idxOrig; ++i) {
            std::memcpy(temp, base, n * sizeof(int));
            OrdenadorUniversal ord(temp, n, a, b, c, seed);
            ord.quicksort(0, n - 1, mpsOrig[i]);

            custosOrig[i] = ord.calculaCusto();
            cmpOrig[i] = ord.cmp;
            movOrig[i] = ord.move;
            callsOrig[i] = ord.calls;

            printf("mps %d cost %.9f cmp %d move %d calls %d\n",
                   mpsOrig[i], custosOrig[i], cmpOrig[i], movOrig[i], callsOrig[i]);
        }


        // Determina o melhor MPS com menor custo
        int melhorIdx = menorCusto(custosOrig, idxOrig);
        melhorValor = mpsOrig[melhorIdx];

        // Prepara para refinar faixa
        double custos[100];
        int mpsVals[100];
        for (int i = 0; i < idxOrig; ++i) {
            custos[i] = custosOrig[i];
            mpsVals[i] = mpsOrig[i];
        }

        calculaNovaFaixa(minMPS, maxMPS, passoMPS, melhorIdx, idxOrig, mpsVals);

        // Encontra índices de minMPS e maxMPS na lista
        int idxMin = -1, idxMax = -1;
        for (int i = 0; i < idxOrig; ++i) {
            if (mpsVals[i] == minMPS) idxMin = i;
            if (mpsVals[i] == maxMPS) idxMax = i;
        }

        if (idxMin == -1 || idxMax == -1) {
            fprintf(stderr, "Erro: minMPS %d ou maxMPS %d não encontrados\n", minMPS, maxMPS);
            break;
        }

        mpsDiff = fabs(custos[idxMin] - custos[idxMax]);
        printf("nummps %d limParticao %d mpsdiff %.6f\n\n", idxOrig, melhorValor, mpsDiff);

        if (idxOrig < 5) break;

        iter++;
    }

    return melhorValor;
}

int OrdenadorUniversal::determinaLimiarQuebras(int limiarParticao, double limiarCusto) {
    int nextLQ = 1;
    int maxLQ = n / 2;
    int passo = 1;              // inicia com passo 1 (testa todos)

    double diffCusto = limiarCusto + 1;
    int melhorLQ = 1;
    int count = 6;

    // Arrays para guardar custos e estatísticas
    double custosQS[1001], custosIN[1001], diffCustos[1001];
    char estatQS[1001][300], estatIN[1001][300];

    static int base[10000], embaralhado[10000], embaralhados[1001][10000];
    static int tempQS[10000], tempIN[10000];

    std::memcpy(base, v, n * sizeof(int));
    ordenaPorInsercao(base, n);

    // Pré-calcula vetores embaralhados para todos os lq possíveis
    for (int lq = 1; lq <= maxLQ; ++lq) {
        std::memcpy(embaralhado, base, n * sizeof(int));
        srand48(seed);
        shuffleVector(embaralhado, n, lq);
        std::memcpy(embaralhados[lq], embaralhado, n * sizeof(int));
    }

    int iter = 0;

    // Pré-cálculo completo com passo 1 para custos iniciais
    while (nextLQ <= maxLQ) {
        std::memcpy(tempQS, embaralhados[nextLQ], n * sizeof(int));
        std::memcpy(tempIN, embaralhados[nextLQ], n * sizeof(int));

        OrdenadorUniversal ordQS(tempQS, n, a, b, c, seed);
        ordQS.quicksort(0, n - 1, limiarParticao);
        custosQS[nextLQ - 1] = ordQS.calculaCusto();
        sprintf(estatQS[nextLQ - 1], "lq %d cost %.9f cmp %d move %d calls %d\n",
                nextLQ, custosQS[nextLQ - 1], ordQS.cmp, ordQS.move, ordQS.calls);

        OrdenadorUniversal ordIN(tempIN, n, a, b, c, seed);
        ordIN.insercao(0, n - 1);
        custosIN[nextLQ - 1] = ordIN.calculaCusto();
        sprintf(estatIN[nextLQ - 1], "lq %d cost %.9f cmp %d move %d calls %d\n",
                nextLQ, custosIN[nextLQ - 1], ordIN.cmp, ordIN.move, ordIN.calls);

        diffCustos[nextLQ - 1] = fabs(custosQS[nextLQ - 1] - custosIN[nextLQ - 1]);

        nextLQ++;
    }

    // Recomeça com passo = 20% da faixa
    nextLQ = 1;
    passo = (int)(maxLQ * 0.2) - 1;
    if (passo < 1) passo = 1;
    diffCusto = limiarCusto + 1;

    while (diffCusto >= limiarCusto && count >= 5) {
        int lqList[100];
        int numLQ = 0;
        melhorLQ = 1;
        count = 0;

        printf("\niter %d\n", iter++);

        while (nextLQ <= maxLQ) {
            lqList[numLQ++] = nextLQ;

            printf("qs %s", estatQS[nextLQ - 1]);
            printf("in %s", estatIN[nextLQ - 1]);

            if (diffCustos[nextLQ - 1] < diffCustos[melhorLQ - 1]) {
                melhorLQ = nextLQ;
            }

            nextLQ += passo;
            count++;
        }

        // Usa lqList para calcular diffCusto baseado nos extremos da faixa (evita warning)
        int iMelhor = -1;
        for (int i = 0; i < numLQ; ++i) {
            if (lqList[i] == melhorLQ) {
                iMelhor = i;
                break;
            }
        }
        if (iMelhor >= 1 && iMelhor + 1 < numLQ) {
            diffCusto = fabs(custosIN[lqList[iMelhor + 1] - 1] - custosIN[lqList[iMelhor - 1] - 1]);
        } else if (iMelhor == 0 && numLQ >= 3) {
            diffCusto = fabs(custosIN[lqList[2] - 1] - custosIN[lqList[0] - 1]);
        } else if (numLQ >= 3) {
            diffCusto = fabs(custosIN[lqList[numLQ - 1] - 1] - custosIN[lqList[numLQ - 3] - 1]);
        } else {
            diffCusto = limiarCusto + 1;
        }

        printf("numlq %d limQuebras %d lqdiff %.6f\n\n", count, melhorLQ, (float)diffCusto);

        if (iMelhor == 0 && numLQ >= 3) {
            nextLQ = lqList[0];
            maxLQ = lqList[2];
        } else if (iMelhor == numLQ - 1 && numLQ >= 3) {
            nextLQ = lqList[numLQ - 3];
            maxLQ = lqList[numLQ - 1];
        } else if (iMelhor > 0 && iMelhor + 1 < numLQ) {
            nextLQ = lqList[iMelhor - 1];
            maxLQ = lqList[iMelhor + 1];
        } else {
            break;  // faixa insuficiente, encerra iteração
        }

        passo = std::max(1, (maxLQ - nextLQ) / 5);

    }
    
    return melhorLQ;
}
