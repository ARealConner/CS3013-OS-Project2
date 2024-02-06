#include "../include/shared.h"
#include "../include/rugby.h"
#include "../include/football.h"
#include "../include/baseball.h"
#include "../include/utils.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


int main() {
	initialize_shared_resources();

	current_game = choose_next_sport();

	pthread_t rugby_threads[TOTAL_RUGBY_PLAYERS];
	pthread_t football_threads[TOTAL_FOOTBALL_PLAYERS];
	pthread_t baseball_threads[TOTAL_BASEBALL_PLAYERS];

	seed_random_number_generator_from_file("seed.txt");

	printf("Worcester Gompei Park Open!\n");

	for (int i = 0; i < TOTAL_RUGBY_PLAYERS; i++) {
		int *id = malloc(sizeof(int));
		*id = i + 1;
		pthread_create(&rugby_threads[i], NULL, rugby_player_thread, id);
	}

	for (int i = 0; i < TOTAL_FOOTBALL_PLAYERS; i++) {
		int *id = malloc(sizeof(int));
		*id = i + 1;
		pthread_create(&football_threads[i], NULL, football_player_thread, id);
	}

	for (int i = 0; i < TOTAL_BASEBALL_PLAYERS; i++) {
		int *id = malloc(sizeof(int));
		*id = i + 1;
		pthread_create(&baseball_threads[i], NULL, baseball_player_thread, id);
	}

	for (int i = 0; i < TOTAL_RUGBY_PLAYERS; i++) {
		pthread_join(rugby_threads[i], NULL);
	}

	for (int i = 0; i < TOTAL_FOOTBALL_PLAYERS; i++) {
		pthread_join(football_threads[i], NULL);
	}

	for (int i = 0; i < TOTAL_BASEBALL_PLAYERS; i++) {
		pthread_join(baseball_threads[i], NULL);
	}

	destroy_shared_resources();

	printf("Worcester Gompei Park Closed!");

	return 0;
}