import pandas as pd
import plotly.graph_objects as go

# Lê o CSV sem cabeçalho
df = pd.read_csv("resultados.csv", names=["Arquivo", "Tempo de Execução (s)"], encoding="utf-8-sig")

# Detecta o tipo e valor numérico
tipos = []
valores = []

for nome in df["Arquivo"]:
    if "pacote" in nome:
        tipos.append("pacotes")
        valores.append(int(nome.split(".")[1]))
    elif "grafo" in nome:
        tipos.append("armazens")
        valores.append(int(nome.split(".")[1]))
    elif "rearmazenamento" in nome:
        tipos.append("rearmazenamentos")
        valores.append(int(nome.split(".")[1]))
    else:
        tipos.append("outro")
        valores.append(0)

df["Tipo"] = tipos
df["Valor"] = valores

# Cria 3 DataFrames separados
df_pacotes = df[df["Tipo"] == "pacotes"].sort_values("Valor")[["Valor", "Tempo de Execução (s)"]]
df_armazens = df[df["Tipo"] == "armazens"].sort_values("Valor")[["Valor", "Tempo de Execução (s)"]]
df_rearmazenamentos = df[df["Tipo"] == "rearmazenamentos"].sort_values("Valor")[["Valor", "Tempo de Execução (s)"]]

# Renomear colunas para visual
df_pacotes.columns = ["Número de Pacotes", "Tempo de Execução (s)"]
df_armazens.columns = ["Número de Armazéns", "Tempo de Execução (s)"]
df_rearmazenamentos.columns = ["Número de Rearmazenamentos", "Tempo de Execução (s)"]

# Função para gerar imagem de tabela
def gerar_tabela(df, titulo, nome_arquivo):
    fig = go.Figure(data=[go.Table(
        header=dict(values=list(df.columns),
                    fill_color='#A6CEE3',
                    align='center',
                    font=dict(size=14, color='black')),
        cells=dict(values=[df[col] for col in df.columns],
                   fill_color='#E0F3F8',
                   align='center',
                   font=dict(size=12))
    )])

    fig.update_layout(title_text=titulo, title_font_size=18, margin=dict(l=0, r=0, t=40, b=0))
    fig.write_image(nome_arquivo, width=800, height=400)
    print(f"✅ Tabela gerada: {nome_arquivo}")

# Gerar cada uma
gerar_tabela(df_pacotes, "Tabela – Número de Pacotes", "tabela_pacotes.png")
gerar_tabela(df_armazens, "Tabela – Número de Armazéns", "tabela_armazens.png")
gerar_tabela(df_rearmazenamentos, "Tabela – Número de Rearmazenamentos", "tabela_rearmazenamentos.png")
