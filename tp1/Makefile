# Variáveis
CXX = g++
CXXFLAGS = -Wall -std=c++11 -Iinclude

SRC = src/main.cpp src/OrdenadorUniversal.cpp
OBJ = obj/main.o obj/OrdenadorUniversal.o
BIN = bin/tp1.out

PYTHON = python3
SCRIPTS_DIR = scripts
INPUTS_DIR = inputs
OUTPUTS_DIR = outputs

.PHONY: all clean run test analise

all: $(BIN)

$(BIN): $(OBJ)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $@ $^

obj/%.o: src/%.cpp
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf obj/* bin/* $(OUTPUTS_DIR)/*.txt $(OUTPUTS_DIR)/*.csv

run: $(BIN)
	./$(BIN) < $(INPUTS_DIR)/input_1.txt

test: $(BIN)
	mkdir -p $(OUTPUTS_DIR)
	for file in $(INPUTS_DIR)/*.txt; do \
		base=$$(basename $$file .txt); \
		echo "Executando $$file..."; \
		./$(BIN) < $$file > $(OUTPUTS_DIR)/$${base}_output.txt; \
	done

analise:
	$(PYTHON) $(SCRIPTS_DIR)/analisa_saida.py
	$(PYTHON) $(SCRIPTS_DIR)/analisa_regressao.py