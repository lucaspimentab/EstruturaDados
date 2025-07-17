CXX = g++
CXXFLAGS = -Wall
BINDIR = bin

OBJS = main.o Heap.o

all: $(BINDIR)/pa3.out

$(BINDIR)/pa3.out: $(OBJS)
	mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o $(BINDIR)/pa3.out