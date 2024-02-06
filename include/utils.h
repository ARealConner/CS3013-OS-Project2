#ifndef PROJECT2_UTILS_H
#define PROJECT2_UTILS_H

#include "shared.h"

void seed_random_number_generator_from_file(const char* filename);
GameState choose_next_sport();
pthread_cond_t* get_cond_for_game(GameState game);

extern int terminate;


#endif //PROJECT2_UTILS_H