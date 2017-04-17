#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace Display
{
bool init();
void clear();
void update();
bool checkForClose();
bool isOpen();
void close();
}

#endif /* DISPLAY_H_ */
