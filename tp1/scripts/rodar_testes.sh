#!/bin/bash

EXEC="./bin/tp1.out"
mkdir -p ../outputs

for file in ./inputs/*.txt; do
  base=$(basename "$file" .txt)
  echo "Executando para $file ..."
  $EXEC < "$file" > "./outputs/${base}_output.txt"
done
