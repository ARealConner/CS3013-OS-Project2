#include "../include/rugby.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define RUGBY_PLAYERS 60
#define RUGBY_GAME_SIZE 30

pthread_mutex_t rugby_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t rugby_cond = PTHREAD_COND_INITIALIZER;
int rugby_players_waiting = 0;

void* play_rugby(void* arg) {
    Player* player = (Player*) arg;

    pthread_mutex_lock(&rugby_mutex);
    rugby_players_waiting++;

    while (rugby_players_waiting % 2 != 0 || rugby_players_waiting > RUGBY_GAME_SIZE) {
        pthread_cond_wait(&rugby_cond, &rugby_mutex);
    }

    printf("Rugby player %d is ready to play.\n", player->id);
    rugby_players_waiting--;

    if (rugby_players_waiting % 2 == 0 && rugby_players_waiting <= RUGBY_GAME_SIZE) {
        pthread_cond_signal(&rugby_cond);
    }

    pthread_mutex_unlock(&rugby_mutex);

    // Simulate the game
    int game_time = rand() % 10 + 1; // Game time is a random number between 1 and 10
    sleep(game_time);

    printf("Rugby player %d has finished playing.\n", player->id);

    return NULL;
}