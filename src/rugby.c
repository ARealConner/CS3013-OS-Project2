#include "../include/shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* rugby_player_thread(void* arg)
{
	int id = *(int*)arg;
	free(arg);

	usleep(rand() % 100000); // Simulate random arrival

	pthread_mutex_lock(&lock);
	while (current_game != NO_GAME || current_game == FOOTBALL_GAME || is_rugby_turn != 1)
	{
		pthread_cond_wait(&cond_rugby, &lock);
	}

	rugby_players_on_field++;
	// Print "Pair Ready" for the first player of each new pair
	if (rugby_players_on_field % 2 == 1)
	{
		printf("\t\t[Rugby: %d] Pair Ready\n", id);
	}

	// Determine the number of players required to start the rugby game randomly within the allowed range
	int required_players = 2 * ((rand() % 15) + 1); // Random even number between 2 and 30

	if (rugby_players_on_field == required_players)
	{
		current_game = RUGBY_GAME; // Start the game with the determined number of players
	}

	printf("\t\t[Rugby: %d] Playing at position %d\n", id, rugby_players_on_field);
	pthread_mutex_unlock(&lock);

	usleep(rand() % 100000); // Simulate game duration

	pthread_mutex_lock(&lock);
	rugby_players_on_field--;
	if (rugby_players_on_field == 0)
	{
		printf("\t\t[Rugby: %d] Game <<ENDED>>\n", id);
		current_game = NO_GAME;
		is_rugby_turn = 0; // Switch to football
		pthread_cond_broadcast(&cond_football); // Signal football players
	}
	pthread_mutex_unlock(&lock);

	return NULL;
}
