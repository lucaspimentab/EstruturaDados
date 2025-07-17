CXX = g++
CXXFLAGS = -Wall -std=c++11 -Iinclude
OBJDIR = obj
BINDIR = bin
SRCDIR = src

OBJS = $(OBJDIR)/main.o $(OBJDIR)/unionFind.o
EXEC = $(BINDIR)/pa4.out

all: $(EXEC)

$(EXEC): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp include/unionFind.hpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/unionFind.o: $(SRCDIR)/unionFind.cpp include/unionFind.hpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)