# Makefile para PA01

CC = gcc
CFLAGS = -Wall -Iinclude
OBJDIR = obj
BINDIR = bin
SRCDIR = src

TARGET = pa1.out

SRC = $(SRCDIR)/evalenum.c
OBJ = $(OBJDIR)/evalenum.o

all: $(BINDIR)/$(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR)/$(TARGET): $(OBJ)
	@mkdir -p $(BINDIR)
	@$(CC) $(CFLAGS) -o $@ $^

clean:
	@rm -rf $(OBJDIR)/*.o $(BINDIR)/$(TARGET)