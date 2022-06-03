#ifndef DeathScene_hpp
#define DeathScene_hpp

#include "KGLEngine/Engine.hpp"
#include "Game/UI/Constant.hpp"

class DeathScene {
public: 
	Engine* engine;
	SpriteNode* background;
	SpriteNode* logo;
	SpriteNode* blackout;
	Texture* defeat;
	Texture* victory;
public:
	bool endplay = false;
	DeathScene(Engine* e);
	~DeathScene() = default;
	void display(bool win, int* pro);
};

#endif
