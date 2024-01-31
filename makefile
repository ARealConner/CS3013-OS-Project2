CC = gcc
CFLAGS = -Wall -Wextra -pthread
DEPS = include/player.h include/baseball.h include/football.h include/rugby.h include/utils.h
OBJ = src/player.c src/baseball.c src/football.c src/rugby.c src/utils.c src/main.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o main