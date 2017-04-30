// Copyright 2017 Andy Taylor
#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include <vector>
#include "Terrain/Terrain.h"

class Camera;
class Player;

class EventHandler {
 public:
    EventHandler();
    void input(Camera* camera, Player* player, std::vector<Terrain>* terrains);
};

#endif /* EVENTHANDLER_H_ */
