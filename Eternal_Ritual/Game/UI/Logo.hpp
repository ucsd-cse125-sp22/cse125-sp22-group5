#ifndef Logo_hpp
#define Logo_hpp

#include "KGLEngine/Engine.hpp"
#include "Game/UI/Constant.hpp"

class Logo{
protected:
	Engine* engine;
	SpriteNode* background;
	SpriteNode* logoPic;
	SpriteNode* light;
	SpriteNode* nameBackground;
	SpriteNode* loadingbar;
	TextNode* loadingText;
	TextNode* name;
	Font* font;
	int* pro;
	bool isload;
	bool isPlaying;
public:
	Logo(Engine* e, Font* font, UINode* parentNode, int* process);
	~Logo() = default;
	void play();
	void updateLoad(float loadingProgess);
};
#endif