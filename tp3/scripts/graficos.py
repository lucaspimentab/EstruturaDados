import pandas as pd
import matplotlib.pyplot as plt

# ================================
# Carrega os CSVs
# ================================
df_pacotes = pd.read_csv("resultados_pacotes.csv")
df_clientes = pd.read_csv("resultados_clientes.csv")
df_armazens = pd.read_csv("resultados_armazens.csv")

# Converte colunas para float
df_pacotes["TempoProcessamento"] = df_pacotes["TempoProcessamento"].astype(float)
df_clientes["TempoProcessamento"] = df_clientes["TempoProcessamento"].astype(float)
df_armazens["TempoProcessamento"] = df_armazens["TempoProcessamento"].astype(float)

# ================================
# Configuração geral do estilo
# ================================
plt.rcParams.update({
    'font.size': 14,
    'figure.figsize': (10,6),
    'axes.grid': True,
    'grid.linestyle': '--',
    'grid.alpha': 0.7
})

# ================================
# Gráfico 1: Pacotes
# ================================
plt.plot(df_pacotes['Pacotes'], df_pacotes['TempoProcessamento'], 
         marker='o', linestyle='-', color='royalblue', linewidth=2, markersize=8)

plt.xlabel('Número de Pacotes')
plt.ylabel('Tempo de Processamento (s)')
plt.title('Tempo de Processamento vs Número de Pacotes')
plt.tight_layout()
plt.savefig("grafico_pacotes.png", dpi=300)
plt.show()

# ================================
# Gráfico 2: Clientes
# ================================
plt.plot(df_clientes['Clientes'], df_clientes['TempoProcessamento'], 
         marker='s', linestyle='-', color='seagreen', linewidth=2, markersize=8)

plt.xlabel('Número de Clientes')
plt.ylabel('Tempo de Processamento (s)')
plt.title('Tempo de Processamento vs Número de Clientes')
plt.tight_layout()
plt.savefig("grafico_clientes.png", dpi=300)
plt.show()

# ================================
# Gráfico 3: Armazéns
# ================================
plt.plot(df_armazens['Armazens'], df_armazens['TempoProcessamento'], 
         marker='^', linestyle='-', color='darkred', linewidth=2, markersize=8)

plt.xlabel('Número de Armazéns')
plt.ylabel('Tempo de Processamento (s)')
plt.title('Tempo de Processamento vs Número de Armazéns')
plt.tight_layout()
plt.savefig("grafico_armazens.png", dpi=300)
plt.show()
