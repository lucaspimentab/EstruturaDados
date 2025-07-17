#include "../include/pacote.h"
#include <cstdio> // usar printf em vez de std::cout para formatação com zeros à esquerda

void imprimir_evento_armazenado(int tempo, int id, int origem, int secao) {
    printf("%07d pacote %03d armazenado em %03d na secao %03d\n", tempo, id, origem, secao);
}

void imprimir_evento_transporte(int tempo, int id, int origem, int destino) {
    printf("%07d pacote %03d em transito de %03d para %03d\n", tempo, id, origem, destino);
}

void imprimir_evento_removido(int tempo, int id, int origem, int secao) {
    printf("%07d pacote %03d removido de %03d na secao %03d\n", tempo, id, origem, secao);
}

void imprimir_evento_rearmazenado(int tempo, int id, int origem, int secao) {
    printf("%07d pacote %03d rearmazenado em %03d na secao %03d\n", tempo, id, origem, secao);
}

void imprimir_evento_entregue(int tempo, int id, int destino) {
    printf("%07d pacote %03d entregue em %03d\n", tempo, id, destino);
}