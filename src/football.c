#include "../include/shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *football_player_thread(void *arg) {
	int id = *(int *)arg;
	free(arg);

	usleep(rand() % 100000); // Simulate random arrival

	pthread_mutex_lock(&lock);
	while (current_game != NO_GAME || current_game == RUGBY_GAME || is_rugby_turn != 0) {
		pthread_cond_wait(&cond_football, &lock);
	}

	football_players_on_field++;
	if (football_players_on_field == 1) {
		printf("[FOOTBALL] Team Ready\n");
	}
	if (football_players_on_field == 22) {
		current_game = FOOTBALL_GAME;
		printf("[FOOTBALL: %d] Game <<STARTED>>\n", id);
	}

	printf("[FOOTBALL: %d] Playing at Position %d\n", id, football_players_on_field);
	pthread_mutex_unlock(&lock);

	usleep(rand() % 100000); // Simulate game duration

	pthread_mutex_lock(&lock);
	football_players_on_field--;
	if (football_players_on_field == 0) {
		printf("[FOOTBALL: %d] Game <<ENDED>>\n", id);
		current_game = NO_GAME;
		is_rugby_turn = 1; // Switch back to rugby
		pthread_cond_broadcast(&cond_rugby); // Signal rugby players
	}
	pthread_mutex_unlock(&lock);

	return NULL;
}
