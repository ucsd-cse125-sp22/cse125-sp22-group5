#ifndef StartSceneUI_hpp
#define StartSceneUI_hpp

#include "KGLEngine/Engine.hpp"
#include "Game/UI/Constant.hpp"

class StartSceneUI {
private:
	SpriteNode* nameBackground;
	TextNode* name;
public:
	StartSceneUI(Engine* e, Font* font);
	~StartSceneUI() = default;

};

#endif