#include "../include/shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *football_player_thread(void *arg) {
	int id = *(int *)arg;
	free(arg);

	usleep(rand() % 100000); // Simulate random arrival

	pthread_mutex_lock(&lock);
	while (current_game == RUGBY_GAME || football_players_on_field >= 22) {
		pthread_cond_wait(&cond_football, &lock);
	}

	if (football_players_on_field == 0) {
		printf("[FOOTBALL] Team Ready\n");
	}
	football_players_on_field++;
	if (football_players_on_field == 1) {
		current_game = FOOTBALL_GAME;
		printf("[FOOTBALL: %d] Game <<STARTED>>\n", id);
	}
	pthread_mutex_unlock(&lock);

	printf("[FOOTBALL: %d] Playing at Position %d\n", id, football_players_on_field);

	usleep(rand() % 100000); // Simulate game duration

	pthread_mutex_lock(&lock);
	football_players_on_field--;
	if (football_players_on_field == 0) {
		current_game = NO_GAME;
		printf("[FOOTBALL: %d] Game <<ENDED>>\n", id);
		pthread_cond_broadcast(&cond_rugby); // Signal rugby players
	}
	pthread_mutex_unlock(&lock);

	return NULL;
}