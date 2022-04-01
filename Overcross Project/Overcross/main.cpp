
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "variables.hpp"
#include "initializations.hpp"
#include "update.hpp"

int main(int argc, const char * argv[]) {
    
    initializeWindow();
    
    // temporarily initialize the map here:
    map = new Map();
    
    // temporarily set the application state to the game state:
    applicationState = 100;
    
    update();
    
    return(0);
}
