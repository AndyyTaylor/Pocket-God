#include <iostream>

#include "Source/Display.h"
#include "Source/Application.h"

#include <string>

// Source/Terrain/Starting.cpp Source/Terrain/MasterTerrain.cpp Source/Terrain/Passage.cpp Source/Hud/Text.cpp Source/Hud/Rect.cpp Source/Hud/Image.cpp Source/Hud/MasterHUD.cpp Source/Hud/HUDComponent.cpp Source/Player.cpp Source/Camera.cpp Source/Terrain/Terrain.cpp Source/Application.cpp Source/Display.cpp Source/EventHandler.cpp Source/Model.cpp Source/Shaders/Shader_Loader.cpp Source/Shaders/Shader_Program.cpp Source/Math/Matrix.cpp -lSDL2_image -lSDL2 -lglew -framework Opengl -std=c++11

std::string PROJECT_PATH;

int main(int argc, char* argv[])
{
	if (!Display::init())
		return -1;

	std::string s(argv[0]);
	PROJECT_PATH = s.substr(0, s.length()-5);
	std::cout << PROJECT_PATH << std::endl;
	Application app;
	app.runMainGameLoop();

	std::cout << "Hello World" << std::endl;
	return 0;
}
