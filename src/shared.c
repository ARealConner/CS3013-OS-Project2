#include "../include/shared.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_rugby = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_football = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_football_start = PTHREAD_COND_INITIALIZER; // New condition variable
GameState current_game = NO_GAME;
int rugby_players_on_field = 0;
int football_players_on_field = 0;
int is_rugby_turn = 1;  // Initialize to 1 to indicate rugby gets the first turn

void initialize_shared_resources() {
 pthread_mutex_init(&lock, NULL);
 pthread_cond_init(&cond_rugby, NULL);
 pthread_cond_init(&cond_football, NULL);
 pthread_cond_init(&cond_football_start, NULL); // Initialize new condition variable
 current_game = NO_GAME;
 rugby_players_on_field = 0;
 football_players_on_field = 0;
 is_rugby_turn = 1;  // Initialize for rugby to start first
}

void destroy_shared_resources() {
 pthread_mutex_destroy(&lock);
 pthread_cond_destroy(&cond_rugby);
 pthread_cond_destroy(&cond_football);
 pthread_cond_destroy(&cond_football_start); // Destroy new condition variable
}