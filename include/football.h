#ifndef FOOTBALL_H
#define FOOTBALL_H

#include "shared.h"

#define MAX_FOOTBALL_PLAYERS 44

typedef struct {
	int id;
} FootballPlayer;

void *football_player_thread(void *arg);

#endif // FOOTBALL_H
