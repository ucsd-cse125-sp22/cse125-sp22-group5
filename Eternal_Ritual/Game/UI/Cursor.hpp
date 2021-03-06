#ifndef Cursor_hpp
#define Cursor_hpp

#include "KGLEngine/Engine.hpp"
#include "Game/UI/Constant.hpp"

class Cursor {
public:
	Engine* engine;
	SpriteNode* cursor;
public:
    
    glm::vec2 cursorScreenPosition = glm::vec2(0.5f, 0.56f);
    
	Cursor(Engine* e);
	~Cursor() = default;
	void update();
	void isDisable(bool t);
};

#endif
