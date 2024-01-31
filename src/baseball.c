#include "../include/baseball.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BASEBALL_PLAYERS 36
#define BASEBALL_GAME_SIZE 18

pthread_mutex_t baseball_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t baseball_cond = PTHREAD_COND_INITIALIZER;
int baseball_players_waiting = 0;

void* play_baseball(void* arg) {
    Player* player = (Player*) arg;

    pthread_mutex_lock(&baseball_mutex);
    baseball_players_waiting++;

    while (baseball_players_waiting < BASEBALL_GAME_SIZE) {
        pthread_cond_wait(&baseball_cond, &baseball_mutex);
    }

    printf("Baseball player %d is ready to play.\n", player->id);
    baseball_players_waiting--;

    if (baseball_players_waiting >= BASEBALL_GAME_SIZE) {
        pthread_cond_signal(&baseball_cond);
    }

    pthread_mutex_unlock(&baseball_mutex);

    // Simulate the game
    int game_time = rand() % 10 + 1; // Game time is a random number between 1 and 10
    sleep(game_time);

    printf("Baseball player %d has finished playing.\n", player->id);

    return NULL;
}