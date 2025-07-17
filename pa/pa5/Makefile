all: bin/pa5.out

bin/pa5.out: obj/main.o obj/Set.o
	g++ obj/main.o obj/Set.o -o bin/pa5.out

obj/main.o: main.cpp
	g++ -Iinclude -c main.cpp -o obj/main.o

obj/Set.o: src/Set.cpp
	g++ -Iinclude -c src/Set.cpp -o obj/Set.o

clean:
	rm -f obj/*.o bin/pa5.out
