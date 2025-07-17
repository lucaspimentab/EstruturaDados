/**
 * Executa o sistema de consultas do sistema logístico dos Armazéns Hanoi.
 * Processa um arquivo de entrada com eventos e consultas, gerenciando:
 * - o histórico dos pacotes,
 * - e a relação dos pacotes com os clientes (como remetente ou destinatário).
 *
 * Atende consultas do tipo:
 * - PC: histórico completo do pacote até o instante dado,
 * - CL: pacotes associados a um cliente com seus estados atuais.
 *
 * Lê o arquivo uma única vez, monta as estruturas (árvores e listas) e
 * imprime as respostas na saída padrão.
 *
 * Autor: Lucas Pimenta Braga
 * Data: 01/07/2025
 */

#include <cstdio>
#include "consultas.h"

// Função principal que apenas delega a execução das consultas.
// Mantém o main limpo, destacando a modularidade do sistema.
int main(int argc, char* argv[]) {
    executar_consultas(argv[1]);
    return 0;
}