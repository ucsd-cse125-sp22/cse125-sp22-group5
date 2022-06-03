//
//  HPBarNode.cpp
//  KGLEngine
//
//  Created by Jackie Li on 4/27/22.
//

#include "Game/UI/HPBarNode.hpp"

HPBarNode::HPBarNode(Engine* e, Font* font, bool isRed, CharNode* character)
{
	engine = e;
	background = new SpriteNode(UISizes::targetBackSize);
	background->texture = new Texture("/Resources/Game/UI/target_back.png");
	background->renderingOrder = 1000;
	baseNode = new UINode();
	baseNode->parentCoordinatePosition = glm::vec2(0.1, 0.5);
	HpBar = new SpriteNode(UISizes::targetBarSize);
	HpBar->texture = new Texture("/Resources/Game/UI/target_bar.png");
	HpBar->position = glm::vec2(HpBar->size.x,0.5);
	icon = new SpriteNode(UISizes::targetIconSize);
	if (isRed) {
		icon->texture = new Texture("/Resources/Game/UI/target_red.png");
	}
	else {
		icon->texture = new Texture("/Resources/Game/UI/target_blue.png");
	}
	icon->parentCoordinatePosition = glm::vec2(0.1, 0.5);
	name = new TextNode(font, 0.02, 1.0, 0.1);
	name->text = character->name;
	name->parentCoordinatePosition = glm::vec2(0.3, 0.1);

	background->addChildNode(baseNode);
	baseNode->addChildNode(HpBar);
	background->addChildNode(icon);
	background->addChildNode(name);
	character->uiNode = background;
}

void HPBarNode::update(float curHP)
{
	if (curHP > initHp) { curHP = initHp; }
	if (curHP < 0) { curHP = 0; }
	Animation* targetBarChange = new Animation("targetBarChange", 0.3);
	targetBarChange->setVec2Animation(&(baseNode->scale), glm::vec2(curHP / initHp, 1.0));
	engine->playAnimation(targetBarChange);
}
