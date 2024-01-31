#include "../include/player.h"
#include <stdlib.h>

Player* create_player(int id, char* type) {
    Player* player = (Player*) malloc(sizeof(Player));
    player->id = id;
    player->type = type;
    return player;
}