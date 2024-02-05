#ifndef SHARED_H
#define SHARED_H

#include <pthread.h>

typedef enum {
	NO_GAME,
	RUGBY_GAME,
	FOOTBALL_GAME
} GameState;

extern pthread_mutex_t lock;
extern pthread_cond_t cond_rugby;
extern pthread_cond_t cond_football;
extern GameState current_game;
extern int rugby_players_on_field;
extern int football_players_on_field;

void initialize_shared_resources();
void destroy_shared_resources();

#endif