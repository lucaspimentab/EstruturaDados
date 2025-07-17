CC = g++
CFLAGS = -std=c++11 -Wall -Iinclude

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=obj/%.o)

all: bin/tp3.out

bin/tp3.out: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f obj/*.o bin/tp3.out
