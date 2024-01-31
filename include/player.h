#ifndef PROJECT2_PLAYER_H
#define PROJECT2_PLAYER_H

typedef struct {
    int id;
    char* type;
} Player;

Player* create_player(int id, char* type);

#endif //PROJECT2_PLAYER_H