// Developed by Kelin Lyu.
#ifndef Input_hpp
#define Input_hpp

#include <vector>
#include <string>
#include <glm/glm.hpp>


struct InputKeyEvent final {
    int key;
    unsigned int state;
    float stateUpdateTime;
};
class Input final {
public:
    bool initialized;
    std::vector<InputKeyEvent*> keyEvents;
    std::string lastCharacter;
    glm::vec2 latestMousePosition;
    glm::vec2 mousePosition;
    glm::vec2 mouseTranslation;
    float scrollWheelAcceleration;
public:
    Input();
    bool isPressingKey(int key);
    bool wasKeyPressed(int key);
    bool wasKeyReleased(int key);
    float getKeyDuration(int key, float currentTime);
    std::string getLastPressedCharacter();
    glm::vec2 getMouseScreenPosition();
    glm::vec2 getMouseTranslation();
    float getScrollWheelAcceleration();
    ~Input();
    void engineSetInputKeyEvent(int key, unsigned int state, float time, std::string character);
    void engineSetMouseEvent(glm::vec2 position);
    void engineSetScrollWheelEvent(float acceleration);
    void engineUpdateInput();
};
#endif
