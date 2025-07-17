#!/bin/bash

echo "Experimento,Clientes,Pacotes,Armazens,ConsultasCL,ConsultasPC,TempoTotal,TempoProcessamento,NumEventos" > resultados_pacotes.csv
echo "Experimento,Clientes,Pacotes,Armazens,ConsultasCL,ConsultasPC,TempoTotal,TempoProcessamento,NumEventos" > resultados_clientes.csv
echo "Experimento,Clientes,Pacotes,Armazens,ConsultasCL,ConsultasPC,TempoTotal,TempoProcessamento,NumEventos" > resultados_armazens.csv

cl=50
pc=50


# ===== 2. Varia o número de CLIENTES =====
pacotes=10000
armazens=30
clientes=(10 50 100 200 300 400 500 1000 10000 20000 30000 40000 50000 60000 70000 80000 90000 100000)

for c in "${clientes[@]}"; do
    sed -i "s/^.*int numclients = .*/int numclients = $c;/" genwkl3.c
    sed -i "s/^.*int numpackets = .*/int numpackets = $pacotes;/" genwkl3.c
    sed -i "s/^.*int nodes = .*/int nodes = $armazens;/" genwkl3.c
    sed -i "s/^.*int numcl = .*/int numcl = $cl;/" genwkl3.c
    sed -i "s/^.*int numpc = .*/int numpc = $pc;/" genwkl3.c

    echo "==== CLIENTES: $c ===="
    gcc genwkl3.c -o genwkl3

    if bash run.csh; then
        numEventos=$(wc -l < tp3.in)
        timeOutput=$( (time ./../bin/tp3.out tp3.in) 2>&1 1>/dev/null )
        tempoTotal=$(echo "$timeOutput" | grep real | awk '{print $2}')
        tempoProc=$(./../bin/tp3.out tp3.in 2>&1 >/dev/null | grep "Tempo de processamento" | awk '{print $4}')

        echo "CLIENTES,$c,$pacotes,$armazens,$cl,$pc,$tempoTotal,$tempoProc,$numEventos" >> resultados_clientes.csv
    else
        echo "CLIENTES,$c,$pacotes,$armazens,$cl,$pc,ERRO,ERRO,ERRO" >> resultados_clientes.csv
    fi
done

