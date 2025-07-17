CC=g++
CFLAGS=-std=c++11 -Wall -g -Iinclude

OBJDIR=obj
BINDIR=bin
SRCDIR=src

SOURCES=$(wildcard $(SRCDIR)/*.cpp)
OBJECTS=$(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
EXEC=$(BINDIR)/tp3.out

all: $(EXEC)

$(EXEC): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJDIR) $(BINDIR)
