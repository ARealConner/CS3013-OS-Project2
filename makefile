CC = gcc
CFLAGS = -Wall -Wextra -pthread
DEPS = include/utils.h include/rugby.h include/football.h include/baseball.h include/shared.h
OBJ = src/main.o src/utils.o src/rugby.o src/football.o src/baseball.o src/shared.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Project2: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) Project2