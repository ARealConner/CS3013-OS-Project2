#include "../include/shared.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_rugby = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_football = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_baseball = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_rugby_paired = PTHREAD_COND_INITIALIZER;
volatile GameState current_game = NO_GAME;
int remaining_rugby_plays = TOTAL_RUGBY_PLAYERS;
int remaining_football_plays = TOTAL_FOOTBALL_PLAYERS;
int remaining_baseball_plays = TOTAL_BASEBALL_PLAYERS;
int active_rugby_players = 0;
int active_football_players = 0;
int active_baseball_players = 0;
int rugby_games_played = 0;
int football_games_played = 0;
int baseball_games_played = 0;
int game_in_progress = 0;
int rugby_pairs_played = 0;

/**
 * Initialize the shared resources.
 */
void initialize_shared_resources() {
 pthread_mutex_init(&lock, NULL);
 pthread_cond_init(&cond_rugby, NULL);
 pthread_cond_init(&cond_football, NULL);
 pthread_cond_init(&cond_baseball, NULL);
 pthread_cond_init(&cond_rugby_paired, NULL);
 current_game = NO_GAME;
 active_rugby_players = 0;
 active_football_players = 0;
 active_baseball_players = 0;
 rugby_games_played = 0;
 football_games_played = 0;
 baseball_games_played = 0;
 game_in_progress = 0;
 rugby_pairs_played = 0;
}

/**
 * Destroy the shared resources.
 */
void destroy_shared_resources() {
 pthread_mutex_destroy(&lock);
 pthread_cond_destroy(&cond_rugby);
 pthread_cond_destroy(&cond_football);
 pthread_cond_destroy(&cond_baseball);
 pthread_cond_destroy(&cond_rugby_paired);
}