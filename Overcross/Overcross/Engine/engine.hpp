// Developed by Kelin.Lyu.
#ifndef Engine_hpp
#define Engine_hpp
#include "Toolkit/common.h"
#include "input.hpp"
#include "image.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "geometry.hpp"
#include "node.hpp"
class Node;
class Engine final {
private:
    double fps;
    double currentFps;
    double updateTime;
    static void keyboardInteractions(GLFWwindow* window, int key, int code,
                                     int action, int modifiers);
    static void mouseInteractions(GLFWwindow* window, int button,
                                  int action, int modifiers);
    static void mouseMovements(GLFWwindow* window, double x, double y);
    static void scrollWheelInteractions(GLFWwindow* window, double dx, double dy);
public:
    static Engine* main;
    string programDirectory;
    float screenWidth;
    float screenHeight;
    GLFWwindow* window;
    Input* input;
    Node* cameraNode;
    vector<Node*> children;
    Engine(const char* windowTitle,
              float resolutionScaleFactor,
              bool fullscreenMode,
              const char* iconFile,
              double fps);
    void changeResolution(float resolutionScaleFactor);
    void hideMouseCursor();
    void showMouseCursor();
    void addChild(Node* node);
    bool isRunning();
    bool shouldUpdate();
    double getTime();
    double getCurrentFps();
    void terminate();
    ~Engine();
};
#endif
