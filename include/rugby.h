#ifndef RUGBY_H
#define RUGBY_H

#include "shared.h"

#define MAX_RUGBY_PLAYERS 60

typedef struct {
	int id;
} RugbyPlayer;

void *rugby_player_thread(void *arg);

#endif // RUGBY_H
