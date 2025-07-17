#ifndef PACOTE_H
#define PACOTE_H

struct Evento {
    int tempo;
    int tipo;      
    int pacote_id;
    int origem;
    int destino;
};

struct Pacote {
    int id;
    int origem;
    int destino;
    int estado;
    int tempo_chegada;
    int rota[100];
    int tamanho_rota;
    int pos_rota;
};

// Declarações das funções
void imprimir_evento_armazenado(int tempo, int id, int origem, int secao);
void imprimir_evento_transporte(int tempo, int id, int origem, int destino);
void imprimir_evento_removido(int tempo, int id, int origem, int secao);
void imprimir_evento_rearmazenado(int tempo, int id, int origem, int secao);
void imprimir_evento_entregue(int tempo, int id, int destino);

#endif
