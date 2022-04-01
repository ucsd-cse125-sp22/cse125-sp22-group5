
#include "variables.hpp"
#include "initializations.hpp"
#include "interactions.hpp"

void initializeWindow() {
    
    char directory[PATH_MAX];
    if(getcwd(directory, sizeof(directory)) == NULL) {
        fprintf(stderr, "Cannot find the current working directory using getcwd().\n");
        return;
    }
    strcat(directory, "/Resources");
    DIR * dir = opendir(directory);
    if(dir == NULL) {
        fprintf(stderr, "Cannot find the resource folder.\n");
        return;
    }
    resourcesFolderPath = std::string(directory);
    
    glfwTerminate();
    
    if(!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW.\n");
        return;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_DECORATED, GL_FALSE);
    
    GLFWmonitor * monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode * mode = glfwGetVideoMode(monitor);
    
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    
    if(windowMode == 0) {
        window = glfwCreateWindow(800, 600, "Overcross", NULL, NULL);
    }else{
        window = glfwCreateWindow(mode->width, mode->height, "Overcross", monitor, NULL);
    }
    
    if(window == NULL) {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return;
    }
    
    glfwMakeContextCurrent(window);
    
    glfwSetKeyCallback(window, keyboardInteractions);
    glfwSetMouseButtonCallback(window, mouseInteractions);
    glfwSetCursorPosCallback(window, mouseMovements);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}
