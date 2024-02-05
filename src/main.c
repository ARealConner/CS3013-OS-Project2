#include "../include/shared.h"
#include "../include/rugby.h"
#include "../include/football.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_RUGBY_PLAYERS 60
#define NUM_FOOTBALL_PLAYERS 44

int main() {
	initialize_shared_resources();

	pthread_t rugby_threads[NUM_RUGBY_PLAYERS];
	pthread_t football_threads[NUM_FOOTBALL_PLAYERS];

	for (int i = 0; i < NUM_RUGBY_PLAYERS; i++) {
		int *id = malloc(sizeof(int));
		*id = i + 1;
		pthread_create(&rugby_threads[i], NULL, rugby_player_thread, id);
	}

	for (int i = 0; i < NUM_FOOTBALL_PLAYERS; i++) {
		int *id = malloc(sizeof(int));
		*id = i + 1;
		pthread_create(&football_threads[i], NULL, football_player_thread, id);
	}

	for (int i = 0; i < NUM_RUGBY_PLAYERS; i++) {
		pthread_join(rugby_threads[i], NULL);
	}

	for (int i = 0; i < NUM_FOOTBALL_PLAYERS; i++) {
		pthread_join(football_threads[i], NULL);
	}

	destroy_shared_resources();

	return 0;
}