#include <cstdio>
#include <cstring>
#include <ctime>
#include "consultas.h"
#include "pacotes.h"
#include "clientes.h"
#include "eventos.h"

struct EventoComTempo {
    EventoNode* evento;
    long tempo;
};

void executar_consultas(char* nomeArquivo) {
    FILE *fp;
    clock_t startLeitura, endLeitura, startProc, endProc;
    double tempoLeitura, tempoProcessamento;

    startLeitura = clock(); // marca início da leitura

    fp = fopen(nomeArquivo, "r");
    if (!fp) {
        perror("Erro ao abrir arquivo");
        return;
    }

    Pacote* pacotes = nullptr;
    Cliente* clientes = nullptr;
    char linha[200];

    while (fgets(linha, sizeof(linha), fp)) {
        // só lê o arquivo mesmo
    }

    endLeitura = clock();
    tempoLeitura = double(endLeitura - startLeitura) / CLOCKS_PER_SEC;

    fclose(fp);

    // começa de verdade o processamento (com reabertura do arquivo)
    fp = fopen(nomeArquivo, "r");
    if (!fp) {
        perror("Erro ao abrir arquivo (2)");
        return;
    }

    startProc = clock();

    while (fgets(linha, sizeof(linha), fp)) {
        long datahora;
        char cmd[4];
        sscanf(linha, "%ld %s", &datahora, cmd);

        if (strcmp(cmd, "EV") == 0) {
            char tipo[4], pacoteId[10];
            sscanf(linha, "%ld %s %s %s", &datahora, cmd, tipo, pacoteId);

            Evento* ev = novoEvento(datahora, tipo, linha);
            pacotes = inserirPacote(pacotes, pacoteId, ev);

            if (strcmp(tipo, "RG") == 0) {
                char remetente[30], destinatario[30];
                sscanf(linha, "%*d %*s %*s %*s %s %s", remetente, destinatario);
                clientes = inserirCliente(clientes, remetente, pacoteId);
                clientes = inserirCliente(clientes, destinatario, pacoteId);
            }

        } else if (strcmp(cmd, "PC") == 0) {
            char pacoteId[10];
            sscanf(linha, "%ld %s %s", &datahora, cmd, pacoteId);
            printf("%06ld PC %s\n", datahora, pacoteId);

            Pacote* p = buscarPacote(pacotes, pacoteId);
            int count = 0;
            if (p) {
                EventoNode* node = p->primeiroEvento;
                while (node && node->evento->datahora <= datahora) {
                    count++;
                    node = node->prox;
                }
            }
            printf("%d\n", count);

            if (p) {
                EventoNode* node = p->primeiroEvento;
                while (node && node->evento->datahora <= datahora) {
                    printf("%s", node->evento->linhaCompleta);
                    node = node->prox;
                }
            }

        } else if (strcmp(cmd, "CL") == 0) {
            char nomeCliente[30];
            sscanf(linha, "%ld %s %s", &datahora, cmd, nomeCliente);
            printf("%06ld CL %s\n", datahora, nomeCliente);

            Cliente* c = buscarCliente(clientes, nomeCliente);
            EventoComTempo eventosParaImprimir[100000];
            int totalEventosParaImprimir = 0;

            if (c) {
                PacoteCliente* pc = c->pacotes;
                while (pc) {
                    Pacote* p = buscarPacote(pacotes, pc->pacoteId);
                    EventoNode* primeiroRG = p ? p->primeiroEvento : nullptr;
                    EventoNode* ultimoValido = nullptr;

                    EventoNode* node = p ? p->primeiroEvento : nullptr;
                    while (node && node->evento->datahora <= datahora) {
                        ultimoValido = node;
                        node = node->prox;
                    }

                    if (primeiroRG) {
                        eventosParaImprimir[totalEventosParaImprimir++] = {primeiroRG, primeiroRG->evento->datahora};
                    }
                    if (ultimoValido && ultimoValido != primeiroRG) {
                        eventosParaImprimir[totalEventosParaImprimir++] = {ultimoValido, ultimoValido->evento->datahora};
                    }
                    pc = pc->prox;
                }
            }

            for (int i = 0; i < totalEventosParaImprimir - 1; i++) {
                for (int j = i + 1; j < totalEventosParaImprimir; j++) {
                    if (eventosParaImprimir[j].tempo < eventosParaImprimir[i].tempo ||
                        (eventosParaImprimir[j].tempo == eventosParaImprimir[i].tempo &&
                         strcmp(eventosParaImprimir[j].evento->evento->linhaCompleta,
                                eventosParaImprimir[i].evento->evento->linhaCompleta) < 0)) {
                        EventoComTempo temp = eventosParaImprimir[i];
                        eventosParaImprimir[i] = eventosParaImprimir[j];
                        eventosParaImprimir[j] = temp;
                    }
                }
            }

            printf("%d\n", totalEventosParaImprimir);
            for (int i = 0; i < totalEventosParaImprimir; i++) {
                printf("%s", eventosParaImprimir[i].evento->evento->linhaCompleta);
            }
        }
    }

    endProc = clock();
    tempoProcessamento = double(endProc - startProc) / CLOCKS_PER_SEC;

    fclose(fp);

    // imprime tempos separados em stderr
    fprintf(stderr, "Tempo de leitura: %.6f\n", tempoLeitura);
    fprintf(stderr, "Tempo de processamento: %.6f\n", tempoProcessamento);
}
