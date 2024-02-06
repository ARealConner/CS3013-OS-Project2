#include "../include/utils.h"
#include <stdlib.h>
#include <stdio.h>

int terminate = 0;

/**
 * Seed the random number generator from a file.
 * @param filename the file to read the seed from
 */
void seed_random_number_generator_from_file(const char* filename)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		fprintf(stderr, "Could not open seed file: %s\n", filename);
		exit(EXIT_FAILURE);
	}

	char buffer[20];
	if (fgets(buffer, sizeof(buffer), file) == NULL)
	{
		fprintf(stderr, "Could not read seed from file: %s\n", filename);
		exit(EXIT_FAILURE);
	}

	char* endptr;
	long seed = strtol(buffer, &endptr, 10);

	if (endptr == buffer)
	{
		fprintf(stderr, "No digits were found in the seed file: %s\n", filename);
		exit(EXIT_FAILURE);
	}

	fclose(file);

	srand((int)seed);
}

/**
 * Choose the next sport to play based on the number of games played.
 * It will randomly decide unless any sports is behind by MAX_GAMES_BEHIND
 * games in which case it will choose the sport that is behind or if all
 * sports are behind by MAX_GAMES_BEHIND games, it will randomly choose.
 * This should be called with the lock held.
 * @return the next sport to play
 */
GameState choose_next_sport()
{
	int most_games_played = rugby_games_played;
	if (football_games_played > most_games_played)
	{
		most_games_played = football_games_played;
	}
	if (baseball_games_played > most_games_played)
	{
		most_games_played = baseball_games_played;
	}

	GameState games_behind[3];
	int count = 0;

	if (most_games_played - rugby_games_played >= MAX_GAMES_BEHIND && rugby_games_played < MAX_GAMES_PER_PLAYER * 2
			&& remaining_rugby_plays >= REQUIRED_RUGBY_PLAYERS)
	{
		games_behind[count++] = RUGBY_GAME;
	}
	if (most_games_played - football_games_played >= MAX_GAMES_BEHIND
			&& football_games_played < MAX_GAMES_PER_PLAYER * 2 && remaining_football_plays >= REQUIRED_FOOTBALL_PLAYERS)
	{
		games_behind[count++] = FOOTBALL_GAME;
	}
	if (most_games_played - baseball_games_played >= MAX_GAMES_BEHIND
			&& baseball_games_played < MAX_GAMES_PER_PLAYER * 2 && remaining_baseball_plays >= REQUIRED_BASEBALL_PLAYERS)
	{
		games_behind[count++] = BASEBALL_GAME;
	}

	if (count > 0)
	{
		return games_behind[rand() % count];
	}
	else
	{
		// If no games are behind, choose a game that hasn't reached MAX_GAMES_PER_PLAYER*2
		GameState games_available[3];
		int available_count = 0;
		if (rugby_games_played < MAX_GAMES_PER_PLAYER * 2 && remaining_rugby_plays >= REQUIRED_RUGBY_PLAYERS)
		{
			games_available[available_count++] = RUGBY_GAME;
		}
		if (football_games_played < MAX_GAMES_PER_PLAYER * 2 && remaining_football_plays >= REQUIRED_FOOTBALL_PLAYERS)
		{
			games_available[available_count++] = FOOTBALL_GAME;
		}
		if (baseball_games_played < MAX_GAMES_PER_PLAYER * 2 && remaining_baseball_plays >= REQUIRED_BASEBALL_PLAYERS)
		{
			games_available[available_count++] = BASEBALL_GAME;
		}
		if (available_count > 0)
		{
			return games_available[rand() % available_count];
		}
		else
		{
			// If all games have reached MAX_GAMES_PER_PLAYER*2, return NO_GAME
			return NO_GAME;
		}
	}
}

/**
 * Get the condition variable for the given game.
 * @param game the game to get the condition variable for
 * @return the condition variable for the given game
 */
pthread_cond_t* get_cond_for_game(GameState game)
{
	switch (game)
	{
	case RUGBY_GAME:
		return &cond_rugby;
	case FOOTBALL_GAME:
		return &cond_football;
	case BASEBALL_GAME:
		return &cond_baseball;
	default:
		return NULL;
	}
}