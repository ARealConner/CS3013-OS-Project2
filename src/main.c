#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/player.h"
#include "../include/baseball.h"
#include "../include/football.h"
#include "../include/rugby.h"
#include "../include/utils.h"

#define BASEBALL_PLAYERS 36
#define FOOTBALL_PLAYERS 44
#define RUGBY_PLAYERS 60

void* start_game(void* arg) {
    Player* player = (Player*) arg;

    if (player->type == "baseball") {
        play_baseball(player);
    } else if (player->type == "football") {
        play_football(player);
    } else if (player->type == "rugby") {
        play_rugby(player);
    }

    free(player);
    return NULL;
}

int main() {
    pthread_t threads[BASEBALL_PLAYERS + FOOTBALL_PLAYERS + RUGBY_PLAYERS];
    int i;

    // Seed the random number generator
    seed_random_number_generator_from_file("seed.txt");

    // Create and start the baseball players
    for (i = 0; i < BASEBALL_PLAYERS; i++) {
        Player* player = create_player(i, "baseball");
        pthread_create(&threads[i], NULL, start_game, player);
    }

    // Create and start the football players
    for (i = 0; i < FOOTBALL_PLAYERS; i++) {
        Player* player = create_player(i, "football");
        pthread_create(&threads[i + BASEBALL_PLAYERS], NULL, start_game, player);
    }

    // Create and start the rugby players
    for (i = 0; i < RUGBY_PLAYERS; i++) {
        Player* player = create_player(i, "rugby");
        pthread_create(&threads[i + BASEBALL_PLAYERS + FOOTBALL_PLAYERS], NULL, start_game, player);
    }

    // Wait for all the players to finish
    for (i = 0; i < BASEBALL_PLAYERS + FOOTBALL_PLAYERS + RUGBY_PLAYERS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}