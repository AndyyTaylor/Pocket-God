// Copyright 2017 Andy Taylor
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <vector>

#include "../Entity.h"
#include "../Terrain/Terrain.h"

class Player : public Entity {
 public:
    bool movingLeft = false, movingRight = false,
      movingUp = false, movingDown = false,
      movingForward = false, movingBackward = false;

    void update(float dt, std::vector<Terrain>* terrains);
    float coins = 50;
    int prevcoins = 0;
    int selectedItem = -1;
    int prevSelectedItem = -1;
    bool interacting = false;
    bool buy = false;
    bool sell = false;
    
    bool coinsChanged() {
        if (coins != prevcoins){
            prevcoins = coins;
            return true;
        }
        return false;
    }
    
    bool changedSelection() {
        if (prevSelectedItem != selectedItem) {
            prevSelectedItem = selectedItem;
            return true;
        }
        return false;
    }
    
    bool buying() {
        if (buy){
            buy = false;
            return true;
        }
        return false;
    }
    
    bool selling() {
        if (sell) {
            sell = false;
            return true;
        }
        return false;
    }
    
    std::vector<int> itemsowned = {0, 0, 0, 0, 0, 0, 0, 0};
    bool restartGame = false; // Yeah I'm really out of time
    bool gameEnded = false;
    
 protected:
    float speed = 250, jumpheight = 260;
    bool isOnGround = false;
    

    glm::vec3 dpos;
};


#endif  /* PLAYER_H */
