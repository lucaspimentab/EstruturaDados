import matplotlib.pyplot as plt
import csv
import os

# Função para ler os dados do arquivo CSV
def ler_dados_csv(arquivo):
    dados = []
    with open(arquivo, 'r') as f:
        leitor = csv.reader(f)
        for linha in leitor:
            if linha:
                nome_arquivo = linha[0]
                tempo_execucao = float(linha[1])
                dados.append((nome_arquivo, tempo_execucao))
    return dados

# Função para gerar o gráfico e salvar
def gerar_grafico(dados, nome_grafico, x_label, y_label):
    # Organiza os dados
    x_values = []
    tempos = []
    for nome_arquivo, tempo in dados:
        # Extrai o número de pacotes, armazéns ou rearmazenamentos do nome do arquivo
        partes = nome_arquivo.split(".")
        try:
            # Número de pacotes, armazéns ou rearmazenamentos
            x_value = int(partes[1])  # Exemplo para pacote, grafo ou rearmazenamento
            x_values.append(x_value)
        except ValueError:
            # Se não conseguir pegar o valor, por exemplo para "grafo.10_15_rear_8"
            x_values.append(int(partes[0].split("_")[1]))  # Número de armazéns ou pacotes

        tempos.append(tempo)

    # Gera o gráfico
    plt.figure(figsize=(10,6))
    plt.plot(x_values, tempos, marker='o', linestyle='-', color='b', label='Tempo de Execução')

    # Adiciona título e rótulos
    plt.title(f"{y_label} vs {x_label}")
    plt.xlabel(x_label)
    plt.ylabel(y_label)
    
    # Exibe o gráfico
    plt.grid(True)
    plt.legend()

    # Cria a pasta "graficos" caso não exista
    if not os.path.exists('graficos'):
        os.makedirs('graficos')
    
    # Salva o gráfico na pasta 'graficos'
    plt.savefig(f'graficos/{nome_grafico}.png')

    # Exibe o gráfico
    plt.show()

# Função principal para gerar gráficos para diferentes parâmetros
def gerar_graficos_completos(dados):
    # Gerar gráfico de Pacotes vs Tempo de Execução
    gerar_grafico(dados[:10], "grafico_pacotes", "Número de Pacotes", "Tempo de Execução (segundos)")

    # Gerar gráfico de Armazenamentos (Tamanho do Grafo) vs Tempo de Execução
    gerar_grafico(dados[10:14], "grafico_grafo", "Número de Armazenamentos", "Tempo de Execução (segundos)")

    # Gerar gráfico de Rearmazenamentos vs Tempo de Execução
    gerar_grafico(dados[14:], "grafico_rearmazenamento", "Número de Rearmazenamentos", "Tempo de Execução (segundos)")

# Main: Leitura dos dados e geração dos gráficos
dados = ler_dados_csv('resultados.csv')

# Gerar gráficos para todos os parâmetros
gerar_graficos_completos(dados)
