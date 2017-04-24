#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

class Camera;

class EventHandler
{
public:
	EventHandler();
	void input(Camera* camera);

private:
	int prevX, prevY;
};

#endif /* EVENTHANDLER_H_ */
