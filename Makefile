CC = gcc
LIBS = -lm -lSDL2 -lSDL2_image
CFLAGS = -Wall -Wextra -std=c99
SRC = $(shell find -name '*.c')
OBJ = $(SRC:.c=.o)
TARGET = main

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIBS)
	rm -f $(OBJ)