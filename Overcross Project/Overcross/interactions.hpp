
#ifndef interactions_hpp
#define interactions_hpp

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

void keyboardInteractions(GLFWwindow * window, int key, int code, int action, int mods);
void mouseInteractions(GLFWwindow * window, int button, int action, int mods);
void mouseMovements(GLFWwindow * window, double x, double y);

#endif
