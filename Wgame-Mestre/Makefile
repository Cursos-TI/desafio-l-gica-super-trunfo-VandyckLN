# Makefile para o Sistema de Territórios para Jogo de War

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c99

# Arquivos fonte
SOURCES = main.c territorio.c alocacao.c combate.c

# Arquivos objeto
OBJECTS = $(SOURCES:.c=.o)

# Nome do executável
TARGET = war_game_desafiante

all: $(TARGET)

# Regra de compilação do executável
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para compilar os objetos
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar arquivos temporários e executável
clean:
	del *.o $(TARGET).exe

# Executar o programa
run: $(TARGET)
	./$(TARGET)

# Dependências
main.o: main.c territorio.h alocacao.h combate.h
territorio.o: territorio.c territorio.h
alocacao.o: alocacao.c alocacao.h territorio.h
combate.o: combate.c combate.h territorio.h
