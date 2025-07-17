# ===== 3. Varia o número de ARMAZENS =====
pacotes=10000
clientes=100
armazens=(1 10 100 200 300 500 700 1000 1500 2000 3000 5000 10000 1000000)

for a in "${armazens[@]}"; do
    echo "--------------------------------------"
    echo "==== ARMAZENS: $a ===="

    sed -i "s/^.*int numclients = .*/int numclients = $clientes;/" genwkl3.c
    sed -i "s/^.*int numpackets = .*/int numpackets = $pacotes;/" genwkl3.c
    sed -i "s/^.*int nodes = .*/int nodes = $a;/" genwkl3.c
    sed -i "s/^.*int numcl = .*/int numcl = $cl;/" genwkl3.c
    sed -i "s/^.*int numpc = .*/int numpc = $pc;/" genwkl3.c

    echo "[DEBUG] Conteúdo do genwkl3.c alterado:"
    grep -E 'int numclients|int numpackets|int nodes|int numcl|int numpc' genwkl3.c

    echo "[DEBUG] Compilando genwkl3..."
    gcc genwkl3.c -o genwkl3
    echo "[DEBUG] Compilação concluída."

    echo "[DEBUG] Executando run.csh..."
    if bash run.csh; then
        echo "[DEBUG] run.csh gerou tp3.in com $(wc -l < tp3.in) linhas."
        echo "[DEBUG] Exibindo as 5 primeiras linhas do tp3.in:"
        head -n 5 tp3.in

        echo "[DEBUG] Executando ./tp3.out com time..."
        output=$( (time ./../bin/tp3.out tp3.in) 2>&1 )
        echo "[DEBUG] Saída completa do programa:"
        echo "$output"

        numEventos=$(wc -l < tp3.in)
        tempoTotal=$(echo "$output" | grep real | awk '{split($2,a,"m"); split(a[2],b,"s"); print a[1]*60 + b[1] }')
        tempoProc=$(echo "$output" | grep "Tempo de processamento" | awk '{print $4}')

        echo "[DEBUG] tempoTotal=$tempoTotal tempoProc=$tempoProc numEventos=$numEventos"
        echo "ARMAZENS,$clientes,$pacotes,$a,$cl,$pc,$tempoTotal,$tempoProc,$numEventos" >> resultados_armazens.csv
    else
        echo "[ERRO] run.csh falhou"
        echo "ARMAZENS,$clientes,$pacotes,$a,$cl,$pc,ERRO,ERRO,ERRO" >> resultados_armazens.csv
    fi
done
