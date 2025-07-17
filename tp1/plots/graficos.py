import os
import re
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Configura o estilo dos gráficos
sns.set(style="whitegrid")

# Cria a pasta ./plots se não existir
output_dir = "./plots"
os.makedirs(output_dir, exist_ok=True)

# Carrega o dataset completo com limiares
df = pd.read_csv("./outputs/dataset_regressao_com_limiares.csv")

# Converte tempo para milissegundos para facilitar visualização
df['time_ms'] = df['time'] * 1000

# Extrai número de quebras do nome do arquivo
df['num_quebras'] = df['arquivo'].apply(lambda x: int(re.search(r'breaks(\d+)', x).group(1)))

# Gráfico 1: Limiar de partição vs tamanho do vetor
plt.figure(figsize=(8,5))
sns.scatterplot(data=df, x='size', y='limParticao', hue='size', palette='viridis', s=100)
plt.title('Limiar de Partição (mps) vs Tamanho do Vetor')
plt.xlabel('Tamanho do Vetor')
plt.ylabel('Limiar de Partição')
plt.grid(True)
plt.tight_layout()
plt.savefig(f"{output_dir}/limiar_particao_vs_tamanho.png")
plt.close()

# Gráfico 2: Limiar de quebras vs número de quebras
plt.figure(figsize=(8,5))
sns.scatterplot(data=df, x='num_quebras', y='limQuebras', hue='size', palette='coolwarm', s=100)
plt.title('Limiar de Quebras (lq) vs Número de Quebras')
plt.xlabel('Número de Quebras no Vetor')
plt.ylabel('Limiar de Quebras')
plt.grid(True)
plt.tight_layout()
plt.savefig(f"{output_dir}/limiar_quebras_vs_num_quebras.png")
plt.close()

# Gráfico 3: Tempo de execução vs tamanho do vetor, colorido por número de quebras
plt.figure(figsize=(10,6))
scatter = plt.scatter(df['size'], df['time_ms'], c=df['num_quebras'], cmap='magma', s=100)
plt.colorbar(scatter, label='Número de Quebras')
plt.title('Tempo de execução vs Tamanho do vetor e Número de Quebras')
plt.xlabel('Tamanho do Vetor')
plt.ylabel('Tempo de Execução (ms)')
plt.grid(True)
plt.tight_layout()
plt.savefig(f"{output_dir}/tempo_vs_tamanho_num_quebras.png")
plt.close()

# Gráfico 4: Operações médias por tamanho do vetor
plt.figure(figsize=(10,6))
sns.lineplot(data=df, x='size', y='cmp', label='Comparações')
sns.lineplot(data=df, x='size', y='move', label='Movimentações')
sns.lineplot(data=df, x='size', y='calls', label='Chamadas')
plt.title('Operações médias por tamanho do vetor')
plt.xlabel('Tamanho do Vetor')
plt.ylabel('Média das Operações')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig(f"{output_dir}/operacoes_medias_vs_tamanho.png")
plt.close()

# Gráfico 5: Distribuição dos tempos de execução
plt.figure(figsize=(8,5))
sns.histplot(df['time_ms'], bins=30, kde=True)
plt.title('Distribuição dos Tempos de Execução (ms)')
plt.xlabel('Tempo (ms)')
plt.tight_layout()
plt.savefig(f"{output_dir}/distribuicao_tempos.png")
plt.close()

print(f"Todos os gráficos foram salvos na pasta {output_dir}")

