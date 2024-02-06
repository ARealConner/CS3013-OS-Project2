#include "../include/utils.h"
#include "../include/rugby.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define INDENT "\t\t"
#define MAX_RUGBY_PLAYERS 30

/**
 * @brief Function for the rugby player thread.
 *
 * The rugby player thread simulates a rugby player participating in a game.
 * It waits for its turn to play, plays the game, and signals when the game is ended.
 *
 * @param arg A pointer to the ID of the rugby player.
 * @return void* The return value is not used.
 */
void* rugby_player_thread(void* arg)
{
	int id = *(int*)arg;
	free(arg);

	for (int i = 0; i < MAX_GAMES_PER_PLAYER; i++)
	{
		sleep(rand() % MAX_SLEEP_SECONDS); // Simulate random arrival

		pthread_mutex_lock(&lock);

		while (rugby_pairs_played >= MAX_RUGBY_PAIRS_PLAYED || active_rugby_players >= MAX_RUGBY_PLAYERS)
		{
			if (terminate)
			{
				pthread_mutex_unlock(&lock);
				return NULL;
			}
			pthread_cond_wait(&cond_rugby, &lock);
		}

		// Wait for the partner to arrive
		if (active_rugby_players % 2 == 1)
		{
			pthread_cond_wait(&cond_rugby_paired, &lock);
		}
		else
		{
			printf(INDENT "[Rugby: %d] Pair Ready to Play\n", id);
			// Increment the number of pairs formed
			rugby_pairs_played++;
			// Signal the partner to start the game
			pthread_cond_broadcast(&cond_rugby_paired);
		}

		while (current_game != RUGBY_GAME)
		{
			if (terminate)
			{
				pthread_mutex_unlock(&lock);
				return NULL;
			}
			pthread_cond_wait(&cond_rugby, &lock);
		}

		active_rugby_players++;
		int player_number = active_rugby_players;

		if (active_rugby_players == 1)
		{
			printf(INDENT "[Rugby: %d] Game <<STARTED>>\n", id);
		}

		// Determine the number of players required to start the rugby game randomly within the allowed range
		printf(INDENT "[Rugby: %d] Playing at position %d\n", id, player_number);
		pthread_mutex_unlock(&lock);

		sleep(rand() % MAX_SLEEP_SECONDS); // Simulate random duration

		pthread_mutex_lock(&lock);
		active_rugby_players--;
		if ((active_rugby_players == 0 || active_rugby_players >= MAX_RUGBY_PLAYERS) && current_game == RUGBY_GAME)
		{
			current_game = choose_next_sport();
		}
		if (active_rugby_players == 0)
		{
			printf(INDENT "[Rugby: %d] Game <<ENDED>>\n", id);
			// Reset the number of pairs played
			rugby_pairs_played = 0;
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
	remaining_rugby_plays--;
	pthread_mutex_unlock(&lock);
	return NULL;
}