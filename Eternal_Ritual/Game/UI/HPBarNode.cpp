//
//  HPBarNode.cpp
//  KGLEngine
//
//  Created by Jackie Li on 4/27/22.
//

#include "Game/UI/HPBarNode.hpp"
#include <iostream>

HPBarNode::HPBarNode(Engine* e, Font* font, bool isRed, CharNode* character)
{
	engine = e;
	background = new SpriteNode(UISizes::targetBackSize);
	background->texture = new Texture("/Resources/Game/UI/target_back.png");
	background->renderingOrder = 1000;
	baseNode = new UINode();
	baseNode->parentCoordinatePosition = glm::vec2(0.05, 0.5);
	HpBar = new SpriteNode(UISizes::targetBarSize);
	HpBar->texture = new Texture("/Resources/Game/UI/target_bar.png");
	HpBar->position = glm::vec2(HpBar->size.x/2,0);
	icon = new SpriteNode(UISizes::targetIconSize);
	if (isRed) {
		icon->texture = new Texture("/Resources/Game/UI/target_red.png");
	}
	else {
		icon->texture = new Texture("/Resources/Game/UI/target_blue.png");
	}
	icon->parentCoordinatePosition = glm::vec2(0.05, 0.5);
	name = new TextNode(font, 0.02, 1.0, 0.1);
	name->text = character->name;
	name->parentCoordinatePosition = glm::vec2(0.3, 0.1);

	background->addChildNode(baseNode);
	baseNode->addChildNode(HpBar);
	background->addChildNode(icon);
	background->addChildNode(name);
	character->headTop->addChildNode(background);
	initHp = character->health;
}

void HPBarNode::update(float curHp)
{
	if (curHp > initHp) { curHp = initHp; }
	if (curHp < 0) { curHp = 0; }
    if (baseNode->getPositionOnScreen().z < 0) {
        baseNode->isDisabled = true;
    }
    else {
        baseNode->isDisabled = false;
    }
	Animation* targetBarChange = new Animation("targetBarChange", 0.3);
	targetBarChange->setFloatAnimation(&baseNode->scale.x, curHp / initHp);
	engine->playAnimation(targetBarChange);
}
