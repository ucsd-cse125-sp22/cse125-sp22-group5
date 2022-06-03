// Developed by Kelin Lyu.
#ifndef Animation_hpp
#define Animation_hpp

#include <string>
#include <functional>
#include <glm/glm.hpp>

class Animation final {
public:
    std::string name;
    float startTime;
    float duration;
    unsigned int timingMode;
    unsigned int type;
    float* floatVariable;
    float floatOriginalValue;
    float floatValue;
    glm::vec2* vec2Variable;
    glm::vec2 vec2OriginalValue;
    glm::vec2 vec2Value;
    glm::vec3* vec3Variable;
    glm::vec3 vec3OriginalValue;
    glm::vec3 vec3Value;
    glm::vec4* vec4Variable;
    glm::vec4 vec4OriginalValue;
    glm::vec4 vec4Value;
    bool hasCompletionHandler;
    std::function<void()> completionHandler;
public:
    Animation(std::string name, float duration);
    void setFloatAnimation(float* variable, float value);
    void setAngleAnimation(float* variable, float value);
    void setVec2Animation(glm::vec2* variable, glm::vec2 value);
    void setVec3Animation(glm::vec3* variable, glm::vec3 value);
    void setVec4Animation(glm::vec4* variable, glm::vec4 value);
    void setEulerAnglesAnimation(glm::vec3* variable, glm::vec3 value);
    void setLinearTimingMode();
    void setEaseInTimingMode();
    void setEaseOutTimingMode();
    void setEaseInEaseOutTimingMode();
    void setCompletionHandler(std::function<void()> completionHandler);
    ~Animation();
    std::string engineGetAnimationName();
    void engineActivateAnimation();
    float engineCalculateProgress(float timeProgress);
    bool engineShouldRemoveAnimation();
};
#endif
