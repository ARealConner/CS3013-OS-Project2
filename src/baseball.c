#include "../include/shared.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define INDENT "\t"
#define PLAYERS_PER_TEAM 9

/**
 * @brief Baseball player thread function.
 *
 * This function is responsible for handling the behavior of a baseball player thread.
 *
 * @param arg Pointer to the thread identifier.
 * @return Always returns NULL.
 */
void* baseball_player_thread(void* arg)
{
	int id = *(int*)arg;
	free(arg);

	for (int i = 0; i < MAX_GAMES_PER_PLAYER; i++)
	{
		sleep(rand() % MAX_SLEEP_SECONDS); // Simulate random arrival

		pthread_mutex_lock(&lock);
		// Ensure the game is not in progress and the required number of players is not reached
		while (game_in_progress || active_baseball_players >= REQUIRED_BASEBALL_PLAYERS)
		{
			if (terminate)
			{
				pthread_mutex_unlock(&lock);
				return NULL;
			}
			pthread_cond_wait(&cond_baseball, &lock);
		}

		active_baseball_players++;
		int player_number = active_baseball_players;
		// Indicate the team is ready when all the player arrives
		if (active_baseball_players == PLAYERS_PER_TEAM)
		{
			printf(INDENT "[BASEBALL] Team A Ready\n");
		}
		if (active_baseball_players == REQUIRED_BASEBALL_PLAYERS)
		{
			printf(INDENT "[BASEBALL] Team B Ready\n");
		}

		// Wait for the game to start
		while (current_game != BASEBALL_GAME || (active_baseball_players < REQUIRED_BASEBALL_PLAYERS && !game_in_progress))
		{
			if (terminate)
			{
				pthread_mutex_unlock(&lock);
				return NULL;
			}
			pthread_cond_wait(&cond_baseball, &lock);
		}

		// Start the game when the required number of players is reached
		if (player_number == REQUIRED_BASEBALL_PLAYERS)
		{
			printf(INDENT "[BASEBALL: %d] Game <<STARTED>>\n", id); // Ensure the start message is printed once
			game_in_progress = IN_PROGRESS;
			pthread_cond_broadcast(&cond_baseball); // signal the players to start the game
		}
		pthread_mutex_unlock(&lock);

		printf(INDENT "[BASEBALL: %d] Playing at Position %d\n", id, player_number);

		sleep(rand() % MAX_SLEEP_SECONDS); // Simulate game duration

		pthread_mutex_lock(&lock);
		active_baseball_players--;
		if (active_baseball_players == 0)
		{
			printf(INDENT "[BASEBALL: %d] Game <<ENDED>>\n", id);
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
	remaining_baseball_plays--;
	pthread_mutex_unlock(&lock);
	return NULL;
}