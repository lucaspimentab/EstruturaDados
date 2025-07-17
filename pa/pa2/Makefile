CXX = g++
CXXFLAGS = -Wall

TARGET = pa2.out
OBJS = main.o Grafo.o ListaAdjacencia.o

all: $(TARGET)
	cp $(TARGET) bin/pa2.out

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o pa2.out bin/pa2.out
