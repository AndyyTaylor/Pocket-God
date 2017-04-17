#include "EventHandler.h"

#include <iostream>
#include "SDL2/SDL.h"
#include "Display.h"
#include "Model.h"

EventHandler::EventHandler()
{
	
}

void EventHandler::input(Model* model)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		
		if (event.type == SDL_QUIT)
		{
			Display::close();
		} else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT) {
			prevX = event.button.x;
			prevY = event.button.y;
		} else if (event.type == SDL_MOUSEWHEEL)
		{
			model->entity.scale += (float) event.wheel.y/10.0; // MOUSE_WHEEL_SENSITIVITY
			//std::cout << model->entity.scale.x << std::endl;
		}
	}
	int x, y;
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		//std::cout << "Mouse right is down" << std::endl;
		model->entity.rotation.y += (x-prevX)/2;	// /MOUSE_SENSITIVITY
		model->entity.rotation.x -= (y-prevY)/2;
		
		prevX = x;
		prevY = y;
	}
}
