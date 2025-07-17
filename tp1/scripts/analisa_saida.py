import glob
import re
import pandas as pd

def parse_output_file(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()

    time_sec = None
    cmp = None
    move = None
    calls = None
    size = None
    lim_particao = None
    lim_quebras = None

    for line in lines:
        if line.startswith("Tempo de execução:"):
            time_sec = float(re.findall(r"[\d\.]+", line)[0])
        elif line.startswith("cmp"):
            parts = line.strip().split()
            cmp = int(parts[1])
            move = int(parts[3])
            calls = int(parts[5])
        elif line.startswith("size"):
            size = int(re.findall(r"\d+", line)[0])
        elif "limParticao" in line:
            # Exemplo: "nummps 6 limParticao 59 mpsdiff 0.004403"
            m = re.search(r"limParticao (\d+)", line)
            if m:
                lim_particao = int(m.group(1))
        elif "limQuebras" in line:
            # Exemplo: "numlq 6 limQuebras 1 lqdiff 0.057349"
            m = re.search(r"limQuebras (\d+)", line)
            if m:
                lim_quebras = int(m.group(1))

    return time_sec, cmp, move, calls, size, lim_particao, lim_quebras

data = []

for filename in glob.glob("outputs/*_output.txt"):
    time_sec, cmp, move, calls, size, lim_particao, lim_quebras = parse_output_file(filename)
    data.append({
        'arquivo': filename,
        'time': time_sec,
        'cmp': cmp,
        'move': move,
        'calls': calls,
        'size': size,
        'limParticao': lim_particao,
        'limQuebras': lim_quebras
    })

df = pd.DataFrame(data)
df.to_csv("./outputs/dataset_regressao_com_limiares.csv", index=False)
print("Dataset salvo em ./outputs/dataset_regressao_com_limiares.csv")
