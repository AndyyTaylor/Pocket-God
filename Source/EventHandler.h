// Copyright 2017 Andy Taylor
#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

class Camera;
class Player;
class Terrain;

class EventHandler {
 public:
    EventHandler();
    void input(Camera* camera, Player* player, Terrain* terrain);
};

#endif /* EVENTHANDLER_H_ */
