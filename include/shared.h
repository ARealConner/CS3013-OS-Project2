#ifndef SHARED_H
#define SHARED_H

#include <pthread.h>

#define MAX_SLEEP_SECONDS 2 // Maximum number of seconds to sleep
#define IN_PROGRESS 1 // Game in progress
#define NOT_IN_PROGRESS 0 // The Game is not in progress
#define MAX_GAMES_PER_PLAYER 2 // Maximum number of games a player can play
#define MAX_RUGBY_PAIRS_PLAYED 15 // Maximum number of rugby pairs that can play
#define REQUIRED_BASEBALL_PLAYERS 18 // Required number of players for a baseball game
#define REQUIRED_FOOTBALL_PLAYERS 22 // Required number of players for a football game
#define REQUIRED_RUGBY_PLAYERS 2 // Required number of players for a rugby game
#define TOTAL_BASEBALL_PLAYERS 36 // Total number of baseball players
#define TOTAL_FOOTBALL_PLAYERS 44 // Total number of football players
#define TOTAL_RUGBY_PLAYERS 60 // Total number of rugby players
#define MAX_GAMES_BEHIND 1 // Maximum number of games behind the most played game before gaining priority

typedef enum {
 NO_GAME,
 RUGBY_GAME,
 FOOTBALL_GAME,
 BASEBALL_GAME
} GameState; // The state of the game

extern pthread_mutex_t lock; // Mutex lock for shared resources
extern pthread_cond_t cond_rugby; // Condition variable for rugby players
extern pthread_cond_t cond_football; // Condition variable for football players
extern pthread_cond_t cond_baseball; // Condition variable for baseball players
extern pthread_cond_t cond_rugby_paired; // Condition variable for rugby players to pair
extern volatile GameState current_game; // The current game being played
extern int remaining_rugby_plays; // The remaining number of rugby plays
extern int remaining_football_plays; // The remaining number of football plays
extern int remaining_baseball_plays; // The remaining number of baseball plays
extern int active_rugby_players; // The number of active rugby players
extern int active_football_players; // The number of active football players
extern int active_baseball_players; // The number of active baseball players
extern int rugby_games_played; // The number of rugby games played
extern int football_games_played; // The number of football games played
extern int baseball_games_played; // The number of baseball games played
extern int game_in_progress; // The status of the game
extern int rugby_pairs_played; // The number of rugby pairs played

void initialize_shared_resources();
void destroy_shared_resources();

#endif // SHARED_H