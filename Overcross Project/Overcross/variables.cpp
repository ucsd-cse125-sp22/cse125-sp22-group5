
#include "variables.hpp"

int windowMode = 1;
// 0 = 800 x 600 borderless window
// 1 = fullscreen

int applicationState;
// -1 = transition
// 10 = menu
// 100 = game

std::string resourcesFolderPath = "";

GLFWwindow * window;

Map * map;
