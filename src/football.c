#include "../include/shared.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define PLAYERS_PER_TEAM 11
#define INDENT ""


/**
 * @brief Function representing the behavior of a football player thread.
 *
 * @param arg Pointer to the thread's ID.
 * @return void* Always returns NULL.
 */
void* football_player_thread(void* arg)
{
	int id = *(int*)arg;
	free(arg);

	for (int i = 0; i < MAX_GAMES_PER_PLAYER; i++)
	{
		sleep(rand() % MAX_SLEEP_SECONDS); // Simulate random arrival

		pthread_mutex_lock(&lock);
		// Ensure the game is not in progress and the required number of players is not reached
		while (game_in_progress || active_football_players >= REQUIRED_FOOTBALL_PLAYERS)
		{
			if (terminate)
			{
				pthread_mutex_unlock(&lock);
				return NULL;
			}
			pthread_cond_wait(&cond_football, &lock);
		}

		active_football_players++;
		int player_number = active_football_players;
		// Indicate the team is ready when all the players arrive
		if (active_football_players == PLAYERS_PER_TEAM)
		{
			printf(INDENT "[FOOTBALL] Team A Ready\n");
		}
		if (active_football_players == REQUIRED_FOOTBALL_PLAYERS)
		{
			printf(INDENT "[FOOTBALL] Team B Ready\n");
		}

		// Wait for the game to start
		while (current_game != FOOTBALL_GAME || (active_football_players < REQUIRED_FOOTBALL_PLAYERS && !game_in_progress))
		{
			if (terminate)
			{
				pthread_mutex_unlock(&lock);
				return NULL;
			}
			pthread_cond_wait(&cond_football, &lock);
		}

		// Start the game when the required number of players is reached
		if (player_number == REQUIRED_FOOTBALL_PLAYERS)
		{
			printf(INDENT "[FOOTBALL: %d] Game <<STARTED>>\n", id); // Ensure the start message is printed once
			game_in_progress = IN_PROGRESS;
			pthread_cond_broadcast(&cond_football); // signal the players to start the game
		}
		pthread_mutex_unlock(&lock);

		printf(INDENT "[FOOTBALL: %d] Playing at Position %d\n", id, player_number);

		sleep(rand() % MAX_SLEEP_SECONDS); // Simulate game duration

		pthread_mutex_lock(&lock);
		active_football_players--;
		if (active_football_players == 0)
		{
			printf(INDENT "[FOOTBALL: %d] Game <<ENDED>>\n", id);
			game_in_progress = NOT_IN_PROGRESS;
			current_game = choose_next_sport();
			// get the cond to signal the next game
			pthread_cond_t* cond_to_signal = get_cond_for_game(current_game);
			// Signal the next game
			if (cond_to_signal != NULL)
			{
				pthread_cond_broadcast(cond_to_signal);
			} else {
				terminate = 1;
				// signal everyone so they can quit
				pthread_cond_broadcast(&cond_rugby);
				pthread_cond_broadcast(&cond_baseball);
				pthread_cond_broadcast(&cond_football);
			}
		}
		pthread_mutex_unlock(&lock);
	}
	pthread_mutex_lock(&lock);
	remaining_football_plays--;
	pthread_mutex_unlock(&lock);
	return NULL;
}