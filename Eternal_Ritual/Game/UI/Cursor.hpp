#ifndef Cursor_hpp
#define Cursor_hpp

#include "KGLEngine/Engine.hpp"
#include "Game/UI/Constant.hpp"

class Cursor {
private:
	Engine* engine;
	SpriteNode* cursor;
public:
    
    glm::vec2 cursorScreenPosition = glm::vec2(0.5f);
    
	Cursor(Engine* e);
	~Cursor() = default;
	void update();
	void isDisable(bool t);
};

#endif
