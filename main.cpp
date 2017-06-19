// Copyright 2017 Andy Taylor
#include <iostream>

#include <string>

#include "Source/Application.h"
#include "Source/Display.h"


std::string PROJECT_PATH; // NOLINT - POD only for globals

int main(int argc, char* argv[]) {
    if (!Display::init())
      return -1;

    std::string s(argv[0]);
    PROJECT_PATH = s.substr(0, s.length()-5);
    std::cout << PROJECT_PATH << std::endl;
    Application app;
    app.runMainGameLoop();
    

    // std::cout << "Program Finished" << std::endl;
    return 0;
}

/*
g++ Source/Hud/Text.cpp Source/GameObjects/NPC.cpp Source/Hud/Rect.cpp Source/Hud/Image.cpp Source/Hud/MasterHUD.cpp Source/Hud/HUDComponent.cpp Source/GameObjects/Player.cpp Source/Camera.cpp Source/Terrain/Terrain.cpp Source/Application.cpp Source/Display.cpp Source/EventHandler.cpp Source/Model.cpp Source/Shaders/Shader_Loader.cpp Source/Shaders/Shader_Program.cpp Source/Math/Matrix.cpp /usr/local/Cellar/sdl2_image/2.0.1_2/lib/libSDL2_image.a /usr/local/Cellar/sdl2/2.0.5/lib/libSDL2.a /usr/local/Cellar/glew/2.0.0/lib/libGLEW.a /usr/local/Cellar/libpng/1.6.29/lib/libpng16.a -liconv -lobjc -framework Opengl -framework CoreAudio -framework AudioToolbox -framework CoreVideo -framework ForceFeedback -framework Cocoa -framework Carbon -framework IOKit -framework AppKit -framework CoreFoundation -framework CoreGraphics -framework CoreServices -framework Foundation -std=c++11 main.cpp -o main
brew install libpng
Data in same folder as main
must be called main
*/