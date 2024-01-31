#include "../include/football.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define FOOTBALL_PLAYERS 44
#define FOOTBALL_GAME_SIZE 22

pthread_mutex_t football_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t football_cond = PTHREAD_COND_INITIALIZER;
int football_players_waiting = 0;

void* play_football(void* arg) {
    Player* player = (Player*) arg;

    pthread_mutex_lock(&football_mutex);
    football_players_waiting++;

    while (football_players_waiting < FOOTBALL_GAME_SIZE) {
        pthread_cond_wait(&football_cond, &football_mutex);
    }

    printf("Football player %d is ready to play.\n", player->id);
    football_players_waiting--;

    if (football_players_waiting >= FOOTBALL_GAME_SIZE) {
        pthread_cond_signal(&football_cond);
    }

    pthread_mutex_unlock(&football_mutex);

    // Simulate the game
    int game_time = rand() % 10 + 1; // Game time is a random number between 1 and 10
    sleep(game_time);

    printf("Football player %d has finished playing.\n", player->id);

    return NULL;
}