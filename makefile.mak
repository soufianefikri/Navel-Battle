CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm

SRC = main.c functions.c
OBJ = $(SRC:.c=.o)
EXECUTABLE = battleship

all: $(EXECUTABLE)

$(EXECUTABLE): main.o functions.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

main.o: main.c header.h
	$(CC) $(CFLAGS) -c $< -o $@

functions.o: functions.c header.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)

