#include "Display.h"

#include <iostream>

namespace Display
{
SDL_Window* window;

bool initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
		return false;
	
	window = SDL_CreateWindow("Pocket God",
							  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  640, 480,
							  SDL_WINDOW_OPENGL);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_CreateContext(window);
	
	return true;
}

void initGL()
{
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST);
}

bool init()
{
	if (!initSDL())
		return false;
	
	initGL();
	return true;
}

void clear()
{
	glClearColor(1.0, 0.0, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void update()
{
	SDL_GL_SwapWindow(window);
}

bool checkForClose()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			return true;
		}
	}
	return false;
}

void close()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}


}
