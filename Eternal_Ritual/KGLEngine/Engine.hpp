// Developed by Kelin Lyu.
#ifndef Engine_hpp
#define Engine_hpp

#include <vector>
#include <string>
#include <map>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "KGLEngine/System/Input.hpp"
#include "KGLEngine/System/FontLibrary.hpp"
#include "KGLEngine/System/Font.hpp"
#include "KGLEngine/System/Animation.hpp"
#include "KGLEngine/System/AudioBuffer.hpp"
#include "KGLEngine/Shading/Image.hpp"
#include "KGLEngine/Shading/Texture.hpp"
#include "KGLEngine/Shading/Shader.hpp"
#include "KGLEngine/Geometry/Geometry.hpp"
#include "KGLEngine/SkeletalAnimation/Bone.hpp"
#include "KGLEngine/SkeletalAnimation/Animator.hpp"
#include "KGLEngine/Node/Node.hpp"
#include "KGLEngine/Toolkit/keys.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <set>
#include <map>
#include <array>
#include <vector>
#include <thread>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <optional>
#include <algorithm>
#include <filesystem>
#include <type_traits>
#include <unordered_set>
#include <unordered_map>

class Engine final {
public:
    glm::vec2 screenResolution;
    glm::vec2 windowResolution;
    float resolutionScaleFactor;
    GLFWwindow* window;
    float FPS;
    float currentFPS;
    float currentTime;
    float updateTime;
    float deltaTime;
    bool cursorHidden;
    bool cursorLocked;
    Node* rootNode;
    Node* musicNode;
    std::map<std::string, Animation*> animations;
public:
    std::string workingDirectory;
    static Engine* main;
    Input* input;
    CameraNode* mainCameraNode;
    Skybox* skybox;
    std::vector<Geometry*> preparedGeometries;
    std::vector<LightNode*> preparedLightNodes;
    std::vector<LightNode*> preparedLightNodeShadows;
    Engine(const char* windowTitle,
           float resolutionScaleFactor,
           int samples,
           const char* iconFile);
    void hideCursor();
    void showCursor();
    void lockCursor();
    void unlockCursor();
    bool isRunning();
    bool shouldUpdate();
    void addNode(Node* node);
    void playAnimation(Animation* animation);
    void stopAnimation(std::string name);
    void loadMusic(std::string name, AudioBuffer* audio);
    void playMusic(std::string name);
    void stopMusic(std::string name);
    void render();
    void renderDirectionalLightShadowMap(LightNode* directionalLightNode);
    glm::vec2 getScreenResolution();
    glm::vec2 getWindowResolution();
    float getTime();
    float getDeltaTime();
    float getCurrentFPS();
    void terminate();
    ~Engine();
    static void engineReceiveKeyboardInteractions(GLFWwindow* window, int key, int code, int action, int modifiers);
    static void engineReceiveMouseInteractions(GLFWwindow* window, int button, int action, int modifiers);
    static void engineReceiveMouseMovements(GLFWwindow* window, double x, double y);
    static void engineReceiveScrollWheelInteractions(GLFWwindow* window, double dx, double dy);
};

inline void print() {
    std::cerr << std::endl;
}
template <typename T>
inline void printVariable(const T& variable) {
    std::cerr << &variable;
}
inline void printVariable(const bool& variable) {
    std::cerr << (variable ? "true" : "false");
}
inline void printVariable(const int& variable) {
    std::cerr << variable;
}
inline void printVariable(const unsigned int& variable) {
    std::cerr << variable;
}
inline void printVariable(const char& variable) {
    std::cerr << variable;
}
inline void printVariable(const unsigned char& variable) {
    std::cerr << variable;
}
inline void printVariable(const long& variable) {
    std::cerr << variable;
}
inline void printVariable(const unsigned long& variable) {
    std::cerr << variable;
}
inline void printVariable(const float& variable) {
    std::cerr << std::to_string(variable);
}
inline void printVariable(const double& variable) {
    std::cerr << std::to_string(variable);
}
inline void printVariable(const char* variable) {
    std::cerr << variable;
}
inline void printVariable(const std::string& variable) {
    std::cerr << variable;
}
template <typename T>
inline void print(const T& variable) {
    printVariable(variable);
    std::cerr << std::endl;
}
template <typename T, typename...Arguments>
inline void print(const T& argument, const Arguments&...arguments) {
    printVariable(argument);
    std::cerr << " ";
    print(arguments...);
}
inline float systemTime() {
    static std::chrono::time_point startTime = std::chrono::high_resolution_clock::now();
    std::chrono::time_point currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
    return(time);
}
#endif
