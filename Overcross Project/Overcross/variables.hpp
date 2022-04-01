
#ifndef variables_hpp
#define variables_hpp

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "map.hpp"

extern int windowMode;
extern int applicationState;
extern std::string resourcesFolderPath;
extern GLFWwindow * window;
extern Map * map;

#endif
