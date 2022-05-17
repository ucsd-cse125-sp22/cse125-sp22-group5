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


class Engine final {
private:
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
#endif
