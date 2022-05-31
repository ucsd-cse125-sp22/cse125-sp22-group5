#ifndef Cursor_hpp
#define Cursor_hpp

#include "KGLEngine/Engine.hpp"
#include "Game/UI/Constant.hpp"

class Cursor {
private:
	Engine* engine;
	SpriteNode* cursor;
public:
	Cursor(Engine* e);
	~Cursor() = default;
	void update();
	void isDisable(bool t);
};

#endif