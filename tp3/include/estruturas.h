#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

// Estrutura que representa um evento no sistema logístico.
// Guarda o tempo, o tipo do evento e a linha original para saída.
struct Evento {
    long datahora;             // Timestamp do evento
    char tipo[4];               // Tipo do evento: RG, AR, RM, UR, TR, EN
    char linhaCompleta[200];    // Linha completa lida do arquivo, preservada para a saída
};

#endif