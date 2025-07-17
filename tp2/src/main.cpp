#include "../include/simulador.h"
#include <iostream>
#include <fstream>
#include <cstdlib>  // Para rand()
#include <chrono>   // Para medir o tempo de execução

// Função para gerar a matriz de adjacência de forma a garantir conectividade
void gerar_matriz_adjacencia_fixa(std::ofstream& arquivo, int num_armazens) {
    // Matriz fixa de adjacência fornecida (fixa para 8 armazéns)
    int adj[8][8] = {
        {0, 1, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 1},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0}
    };

    // Escreve a matriz de adjacência no arquivo
    for (int i = 0; i < num_armazens; i++) {
        for (int j = 0; j < num_armazens; j++) {
            arquivo << adj[i][j] << " ";
        }
        arquivo << "\n";
    }

    // Debug: imprimir a matriz de adjacência
    std::cout << "Matriz de adjacência gerada para " << num_armazens << " armazéns:" << std::endl;
    for (int i = 0; i < num_armazens; i++) {
        for (int j = 0; j < num_armazens; j++) {
            std::cout << adj[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Função para gerar o arquivo de entrada com base no parâmetro variável (incluindo o tamanho do grafo)
void gerar_arquivo_entrada(const char* nome_arquivo, int num_armazens, int num_pacotes, int capacidade_transporte, int latencia, int intervalo, int custo_remocao, int num_rearmazenamentos) {
    std::ofstream arquivo(nome_arquivo);

    // Escreve os parâmetros fixos no arquivo
    arquivo << capacidade_transporte << "\n";
    arquivo << latencia << "\n";
    arquivo << intervalo << "\n";
    arquivo << custo_remocao << "\n";

    // Escreve o número de armazéns
    arquivo << num_armazens << "\n";

    // Gera e escreve a matriz de adjacência no arquivo, garantindo a conectividade
    gerar_matriz_adjacencia_fixa(arquivo, num_armazens);

    // Gerando pacotes ordenados
    arquivo << num_pacotes << "\n";
    int pacote_id = 801; // Começa com o pacote 801
    for (int i = 0; i < num_pacotes; i++) {
        int tempo_chegada = (i + 1) * 10;  // Tempo de chegada ordenado (10, 20, 30,...)
        int origem = i % num_armazens;  // Origem cíclica
        int destino = (i + 1) % num_armazens;  // Destino cíclico (sempre próximo)
        
        arquivo << tempo_chegada << " pac " << pacote_id++ << " org " << origem << " dst " << destino << "\n";
    }

    // Adicionando o número de rearmazenamentos no arquivo
    arquivo << num_rearmazenamentos << "\n";  // Número de rearmazenamentos

    arquivo.close();
    std::cout << "Arquivo " << nome_arquivo << " gerado com sucesso!" << std::endl;
}

// Função para medir o tempo de execução e realizar a simulação
void medir_tempo_execucao(const char* caminho_entrada) {
    // Inicia a contagem do tempo
    auto start = std::chrono::high_resolution_clock::now();
    
    // Executa a simulação
    executar_simulacao(caminho_entrada);
    
    // Finaliza a contagem do tempo
    auto end = std::chrono::high_resolution_clock::now();
    
    // Calcula a diferença entre os tempos (tempo de execução)
    std::chrono::duration<double> duration = end - start;
    
    // Exibe o tempo de execução
    std::cout << "Tempo de execução para " << caminho_entrada << ": " << duration.count() << " segundos." << std::endl;

    // Salva o tempo de execução em um arquivo CSV (para análise posterior)
    std::ofstream arquivo_resultado("resultados.csv", std::ios_base::app);  // Abre o arquivo no modo de adição

    // Verifica se o arquivo foi aberto corretamente
    if (!arquivo_resultado.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de resultados.csv para escrita." << std::endl;
        return;
    }

    // Adiciona os resultados no arquivo CSV
    arquivo_resultado << caminho_entrada << "," << duration.count() << "\n";  // Grava o nome do arquivo e o tempo de execução
    arquivo_resultado.close();
}

// Função para rodar os testes e gravar os resultados variando o número de rearmazenamentos
void rodar_testes_e_gravar_resultados() {
    // Parâmetros fixos (capacidade de transporte, latência, etc.)
    int capacidade_transporte = 3;  // Capacidade fixa
    int latencia = 30;              // Latência fixa
    int intervalo = 120;            // Intervalo entre transportes
    int custo_remocao = 4;         // Custo de remoção fixo

    // Variação do número de rearmazenamentos
    for (int num_rearmazenamentos : {10, 50, 100, 200, 300, 400, 500, 1000, 10000}) {  // Variação do número de rearmazenamentos
        int num_armazens = 8;  // Número fixo de armazéns (grafo fixo de 8 armazéns)
        int num_pacotes = 15; // Número fixo de pacotes para simplificação

        // Gerar o arquivo de entrada com o número de rearmazenamentos variando
        std::string nome_arquivo = "entradas/shed_" + std::to_string(num_armazens) + "_" + std::to_string(num_pacotes) + "_rear_" + std::to_string(num_rearmazenamentos) + ".wkl";
        gerar_arquivo_entrada(nome_arquivo.c_str(), num_armazens, num_pacotes, capacidade_transporte, latencia, intervalo, custo_remocao, num_rearmazenamentos);

        // Medir o tempo de execução para esse arquivo de entrada
        medir_tempo_execucao(nome_arquivo.c_str());
    }
}

int main() {
    // Chama a função para rodar os testes e gravar os resultados
    rodar_testes_e_gravar_resultados();
    return 0;
}
