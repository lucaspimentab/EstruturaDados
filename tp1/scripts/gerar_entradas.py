# scripts/gerar_entradas.py
import numpy as np
import os

def shuffle_vector(vet, num_breaks, seed):
    np.random.seed(seed)
    size = len(vet)
    vet_sorted = np.sort(vet)
    vet_shuffled = vet_sorted.copy()

    swaps = 0
    while swaps < num_breaks:
        i, j = np.random.choice(size, 2, replace=False)
        vet_shuffled[i], vet_shuffled[j] = vet_shuffled[j], vet_shuffled[i]
        swaps += 1

    return vet_shuffled

def generate_input_file(filename, seed, limiarCusto, a, b, c, size, num_breaks):
    v = np.arange(size)
    v = shuffle_vector(v, num_breaks, seed)

    with open(filename, 'w') as f:
        f.write(f"{seed} {limiarCusto} {a} {b} {c} {size}\n")
        for val in v:
            f.write(f"{val}\n")

if __name__ == "__main__":
    os.makedirs("../inputs", exist_ok=True)

    seed = 1
    limiarCusto = 10000.0
    # Use aqui os coeficientes calibrados
    a = 4.5012360849021245e-05
    b = -1.2345748005851766e-06
    c = 5.646603832604499e-06

    sizes = [100, 500, 1000, 2000]
    breaks = [0, 10, 100, 300, 500]

    for size in sizes:
        for brk in breaks:
            filename = f"./inputs/input_{size}_breaks{brk}.txt"
            generate_input_file(filename, seed, limiarCusto, a, b, c, size, brk)
            print(f"Gerado arquivo: {filename}")