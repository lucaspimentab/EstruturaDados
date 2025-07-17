import pandas as pd
import numpy as np

df = pd.read_csv("outputs/dataset_regressao.csv")

X = df[['calls', 'cmp', 'move']].values
y = df['time'].values * 1000  # tempo em milissegundos

coef, residuals, rank, s = np.linalg.lstsq(X, y, rcond=None)
a, b, c = coef

print(f"Coeficientes estimados:\na = {a}\nb = {b}\nc = {c}")
