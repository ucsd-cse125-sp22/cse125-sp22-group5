
#include "variables.hpp"
#include "interactions.hpp"

void keyboardInteractions(GLFWwindow * window, int key, int code, int action, int mods) {
    
    if(applicationState == 100) {
        
        if(action == GLFW_PRESS) {
            
            printf("Key pressed: %d/n", key);
            
            if(key == GLFW_KEY_ESCAPE) {
                glfwSetWindowShouldClose(window, GL_TRUE);
            }
        }
    }
}

void mouseInteractions(GLFWwindow * window, int button, int action, int mods) {
    
    if(applicationState == 100) {
        
        if(action == GLFW_PRESS) {
            
            printf("Mouse button pressed: %d/n", button);
            
        }
    }
}

void mouseMovements(GLFWwindow * window, double x, double y) {
    
    if(applicationState == 100) {
        
        printf("Mouse position: (x: %f, y: %f)\n", x, y);
        
    }
}
