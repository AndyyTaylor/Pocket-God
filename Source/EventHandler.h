#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

class Model;

class EventHandler
{
public:
	EventHandler();
	void input(Model* model);
	
private:
	int prevX, prevY;
};

#endif /* EVENTHANDLER_H_ */
