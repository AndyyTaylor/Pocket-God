// Copyright 2017 Andy Taylor
#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

class Camera;

class EventHandler {
 public:
    EventHandler();
    void input(Camera* camera);
};

#endif /* EVENTHANDLER_H_ */
