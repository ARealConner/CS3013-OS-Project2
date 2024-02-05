#include "../include/shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern pthread_cond_t cond_football_start; // New condition variable

void *football_player_thread(void *arg) {
 int id = *(int *)arg;
 free(arg);

 usleep(rand() % 100000); // Simulate random arrival

 pthread_mutex_lock(&lock);
 while (current_game != NO_GAME || current_game == RUGBY_GAME || is_rugby_turn != 0) {
  pthread_cond_wait(&cond_football, &lock);
 }

 football_players_on_field++;
 // Indicate team is ready when the first player arrives
 if (football_players_on_field == 1) {
  printf("[FOOTBALL] Team Ready\n");
 }

 // Start the game when the required number of players is reached
 if (football_players_on_field == 22 && current_game != FOOTBALL_GAME) {
  printf("[FOOTBALL: %d] Game <<STARTED>>\n", id); // Ensure the start message is printed once
  current_game = FOOTBALL_GAME;
  pthread_cond_broadcast(&cond_football_start); // Signal all football players that the game has started
 }
 pthread_mutex_unlock(&lock);

 pthread_mutex_lock(&lock);
 while (current_game != FOOTBALL_GAME) {
  pthread_cond_wait(&cond_football_start, &lock); // Wait for the game to start
 }
 pthread_mutex_unlock(&lock);

 printf("[FOOTBALL: %d] Playing at Position %d\n", id, football_players_on_field);

 usleep(rand() % 100000); // Simulate game duration

 pthread_mutex_lock(&lock);
 football_players_on_field--;
 if (football_players_on_field == 0) {
  printf("[FOOTBALL: %d] Game <<ENDED>>\n", id);
  current_game = NO_GAME;
  is_rugby_turn = 1; // Switch back to rugby
  pthread_cond_broadcast(&cond_rugby); // Signal rugby players
 }
 pthread_mutex_unlock(&lock);

 return NULL;
}