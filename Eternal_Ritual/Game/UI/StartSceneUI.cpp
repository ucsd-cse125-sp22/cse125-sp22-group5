#include "StartSceneUI.hpp"

StartSceneUI::StartSceneUI(Engine* e, Font* font)
{
	UINode* base = new UINode();
	nameBackground = new SpriteNode(UISizes::logoBackSize);
	nameBackground->texture = new Texture("/Resources/Game/UI/logo_back.png");
	nameBackground->alpha = 1;

	name = new TextNode(font, 0.15f, 1.0f, 0.1f);
	name->text = "Eternal Ritual";
	name->color = Color::LogotextColor;
	name->parentCoordinatePosition = glm::vec2(0.5, 0.69);

	e->addNode(base);
}
