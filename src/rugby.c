#include "../include/shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *rugby_player_thread(void *arg) {
	int id = *(int *)arg;
	free(arg);

	usleep(rand() % 100000); // Simulate random arrival

	pthread_mutex_lock(&lock);
	while (current_game == FOOTBALL_GAME || rugby_players_on_field >= 30) {
		pthread_cond_wait(&cond_rugby, &lock);
	}

	printf("[Rugby: %d] Pair Ready\n", id);
	rugby_players_on_field++;
	if (rugby_players_on_field == 1) {
		current_game = RUGBY_GAME;
		printf("[Rugby: %d] Game <<STARTED>>\n", id);
	}
	pthread_mutex_unlock(&lock);

	printf("[Rugby: %d] Playing at position %d\n", id, rugby_players_on_field);

	usleep(rand() % 100000); // Simulate game duration

	pthread_mutex_lock(&lock);
	rugby_players_on_field--;
	if (rugby_players_on_field == 0) {
		current_game = NO_GAME;
		printf("[Rugby: %d] Game <<ENDED>>\n", id);
		pthread_cond_broadcast(&cond_football); // Signal football players
	}
	pthread_mutex_unlock(&lock);

	return NULL;
}