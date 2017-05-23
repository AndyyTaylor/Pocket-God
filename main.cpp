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
    // std::cout << PROJECT_PATH << std::endl;
    Application app;
    app.runMainGameLoop();

    // std::cout << "Program Finished" << std::endl;
    return 0;
}
