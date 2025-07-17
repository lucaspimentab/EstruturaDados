import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

sns.set(style="whitegrid")
plt.rcParams.update({'axes.titlesize': 14, 'axes.labelsize': 12, 'legend.fontsize': 10, 'xtick.labelsize': 10, 'ytick.labelsize': 10})

df_otim = pd.read_csv("../outputs/dataset_regressao_com_limiares.csv")
df_nao = pd.read_csv("../outputs/non_optimized_metrics.csv")

df_otim['versao'] = 'Otimizado'
df_nao['versao'] = 'Não Otimizado'
df_otim['alg'] = 'OrdenadorUniversal'

df = pd.concat([
    df_otim[['size', 'time', 'cmp', 'move', 'calls', 'alg', 'versao']],
    df_nao[['size', 'time', 'cmp', 'move', 'calls', 'alg', 'versao']]
])

a, b, c = 4.5012360849021245e-05, -1.2345748005851766e-06, 5.646603832604499e-06
df['custo_estimado'] = a * df['cmp'] + b * df['move'] + c * df['calls']

output_dir = "./tp1/outputs/plots_comparacao_melhor"
os.makedirs(output_dir, exist_ok=True)

palette = {"Otimizado": "#1f77b4", "Não Otimizado": "#ff7f0e"}

fig, axes = plt.subplots(3, 2, figsize=(14, 18))
axes = axes.flatten()

# Gráfico 1: Tempo vs Tamanho
sns.lineplot(data=df, x='size', y='time', hue='versao', style='alg',
             markers=True, dashes=False, ax=axes[0], palette=palette)
axes[0].set_title("Tempo de execução vs Tamanho do vetor")
axes[0].set_xlabel("Tamanho do vetor")
axes[0].set_ylabel("Tempo (s)")
axes[0].grid(True)

# Gráfico 2: Custo estimado vs Tamanho
sns.lineplot(data=df, x='size', y='custo_estimado', hue='versao', style='alg',
             markers=True, dashes=False, ax=axes[1], palette=palette)
axes[1].set_title("Custo estimado (a·cmp + b·move + c·calls) vs Tamanho")
axes[1].set_xlabel("Tamanho do vetor")
axes[1].set_ylabel("Custo estimado")
axes[1].grid(True)

# Gráfico 3: Comparações vs Tamanho
sns.lineplot(data=df, x='size', y='cmp', hue='versao', style='alg',
             markers=True, dashes=False, ax=axes[2], palette=palette)
axes[2].set_title("Comparações vs Tamanho do vetor")
axes[2].set_xlabel("Tamanho do vetor")
axes[2].set_ylabel("Comparações")
axes[2].grid(True)

# Gráfico 4: Movimentações vs Tamanho
sns.lineplot(data=df, x='size', y='move', hue='versao', style='alg',
             markers=True, dashes=False, ax=axes[3], palette=palette)
axes[3].set_title("Movimentações vs Tamanho do vetor")
axes[3].set_xlabel("Tamanho do vetor")
axes[3].set_ylabel("Movimentações")
axes[3].grid(True)

# Gráfico 5: Chamadas de função vs Tamanho
sns.lineplot(data=df, x='size', y='calls', hue='versao', style='alg',
             markers=True, dashes=False, ax=axes[4], palette=palette)
axes[4].set_title("Chamadas de função vs Tamanho do vetor")
axes[4].set_xlabel("Tamanho do vetor")
axes[4].set_ylabel("Chamadas")
axes[4].grid(True)

# Deixa o último subplot em branco
axes[5].axis('off')

# Legenda única
handles, labels = axes[0].get_legend_handles_labels()
fig.legend(handles, labels, loc='upper center', ncol=4, bbox_to_anchor=(0.5, 1.02))

plt.tight_layout(rect=[0, 0, 1, 0.97])
plt.savefig(f"{output_dir}/comparacao_algoritmos_3x2.png")
plt.show()

print(f"✅ Gráfico salvo em {output_dir}/comparacao_algoritmos_3x2.png")
