#include "HUDNode.hpp"
#include <iostream>

HUDNode::HUDNode(Engine* e, UINode* parentNode, bool isRed, Font* font, CharNode* selfChar, CharNode* ally)
{
	engine = e;
	this->parentNode = parentNode;
	this->selfChar = selfChar;
	this->ally = ally;
	glm::vec2 winSize = glm::vec2(engine->getWindowResolution().x/engine->getWindowResolution().y,1.0);
	int id = 0;

	// Main =========================
	mainBackground = new SpriteNode(UISizes::mainBackgroundSize);
	mainBackground->texture = new Texture("/Resources/Game/UI/background_main.png");
	mainHpBar = new BarNode(mainBackground,100,
		new Texture("/Resources/Game/UI/hp_bar_main.png"),
		new Texture("/Resources/Game/UI/hp_bar_fade_main.png"),
		UISizes::mainHpBarSize, UISizes::mainHpFadeBarSize, id++);
	mainHpBar->setPosition(glm::vec2(0.5,0.32));
	mainMpBar = new BarNode(mainBackground, 100,
		new Texture("/Resources/Game/UI/mp_bar_main.png"),
		new Texture("/Resources/Game/UI/mp_bar_fade_main.png"),
		UISizes::mainMpBarSize, UISizes::mainMpFadeBarSize, id++);
	mainMpBar->setPosition(glm::vec2(0.44,0.75));
	mainAvatar = new SpriteNode(UISizes::avatarSize);
	mainAvatar->texture = new Texture("/Resources/Game/UI/human_female.png");
	mainIcon = new SpriteNode(UISizes::avatarIconSize);
	mainIcon->texture = new Texture("/Resources/Game/UI/spell_99.png");
	mainIcon->parentCoordinatePosition = glm::vec2(0.72,0.8);
	mainIcon->scale = glm::vec2(0.2);
	mainName = new TextNode(font, 0.45f, 3, 0.01f);
	mainName->text = "Player Name";
	mainName->scale = glm::vec2(0.11);
	mainName->parentCoordinatePosition = glm::vec2(0.29,-0.13);
	
	if (isRed) {
		mainAvatar->parentCoordinatePosition = glm::vec2(0.118, 0.5);
		mainAvatarBack = new SpriteNode(UISizes::mainAvatarBackRedSize);
		mainAvatarBack->texture = new Texture("/Resources/Game/UI/avatar_back_red.png");
		mainAvatarTop = new SpriteNode(UISizes::mainAvatarRedTopSize);
		mainAvatarTop->texture = new Texture("/Resources/Game/UI/avatar_ver2_red.png");
		mainAvatarTop->parentCoordinatePosition = glm::vec2(0.155, 0.5);
	}
	else {
		mainAvatar->parentCoordinatePosition = glm::vec2(0.231, 0.5);
		mainAvatarBack = new SpriteNode(UISizes::mainAvatarBackBlueSize);
		mainAvatarBack->texture = new Texture("/Resources/Game/UI/avatar_back_blue.png");
		mainAvatarBack->parentCoordinatePosition = glm::vec2(0.335,0.5);
		mainAvatarTop = new SpriteNode(UISizes::mainAvatarBlueTopSize);
		mainAvatarTop->texture = new Texture("/Resources/Game/UI/avatar_ver2_blue.png");
		mainAvatarTop->parentCoordinatePosition = glm::vec2(0.27, 0.5);
	}

	parentNode->addChildNode(mainBackground);
	mainBackground->addChildNode(mainAvatarBack);
	mainAvatarBack->renderingOrder = 2;
	mainBackground->addChildNode(mainName);
	mainAvatarBack->addChildNode(mainAvatar);
	mainAvatarBack->addChildNode(mainAvatarTop);
	mainAvatarTop->addChildNode(mainIcon);
	mainIcon->renderingOrder = 3;

	//---- main size ----
	mainBackground->scale = glm::vec2(winSize.x / UISizes::mainAvatarBackRedSize.x / 3);
	mainBackground->position = glm::vec2(UISizes::mainAvatarBackRedSize.x * mainBackground->scale.x/2 + 0.01,
		UISizes::mainAvatarBackRedSize.y * mainBackground->scale.y / 2 + 0.01);
	
	// party =========================

	partyBackground = new SpriteNode(UISizes::partyBackgroundSize);
	partyBackground->texture = new Texture("/Resources/Game/UI/background_party.png");
	partyHpBar = new BarNode(partyBackground, 100,
		new Texture("/Resources/Game/UI/hp_bar_party.png"),
		new Texture("/Resources/Game/UI/hp_bar_fade_party.png"),
		UISizes::partyHpBarSize, UISizes::partyHpFadeBarSize, id++);
	partyHpBar->setPosition(glm::vec2(0.5, 0.32));
	partyMpBar = new BarNode(partyBackground, 100,
		new Texture("/Resources/Game/UI/mp_bar_party.png"),
		new Texture("/Resources/Game/UI/mp_bar_fade_party.png"),
		UISizes::partyMpBarSize, UISizes::partyMpFadeBarSize, id++);
	partyMpBar->setPosition(glm::vec2(0.44, 0.75));
	partyAvatar = new SpriteNode(UISizes::avatarSize);
	partyAvatar->texture = new Texture("/Resources/Game/UI/human_female.png");
	partyAvatarBack = new SpriteNode(UISizes::partyAvatarBackSize);
	partyAvatarBack->texture = new Texture("/Resources/Game/UI/avatar_back_party.png");
	partyAvatarBack->parentCoordinatePosition = glm::vec2(0.05,0.5);
	partyIcon = new SpriteNode(UISizes::avatarIconSize);
	partyIcon->texture = new Texture("/Resources/Game/UI/spell_99.png");
	partyIcon->parentCoordinatePosition = glm::vec2(0.72, 0.8);
	partyIcon->scale = glm::vec2(0.2);
	partyName = new TextNode(font, 0.45f, 3, 0.01f);
	partyName->text = "Player Name";
	partyName->scale = glm::vec2(0.1);
	partyName->parentCoordinatePosition = glm::vec2(0.35, -0.05);

	if (isRed) {
		partyAvatarTop = new SpriteNode(UISizes::partyAvatarRedTopSize);
		partyAvatarTop->texture = new Texture("/Resources/Game/UI/avatar_ver2_party_red.png");
		partyAvatarTop->parentCoordinatePosition = glm::vec2(0.7, 0.5);
	}
	else {
		partyAvatarTop = new SpriteNode(UISizes::partyAvatarBlueTopSize);
		partyAvatarTop->texture = new Texture("/Resources/Game/UI/avatar_ver2_party_blue.png");
		partyAvatarTop->parentCoordinatePosition = glm::vec2(0.7, 0.5);
	}

	parentNode->addChildNode(partyBackground);
	partyBackground->addChildNode(partyAvatarBack);
	partyAvatarBack->renderingOrder = 2;
	partyBackground->addChildNode(partyName);
	partyAvatarBack->addChildNode(partyAvatar);
	partyAvatarBack->addChildNode(partyAvatarTop);
	partyAvatarTop->addChildNode(partyIcon);
	mainIcon->renderingOrder = 3;

	//---- party size ----
	partyBackground->scale = glm::vec2(winSize.x / UISizes::partyBackgroundSize.x / 5.5);
	partyBackground->position = glm::vec2((UISizes::partyBackgroundSize.x + UISizes::partyAvatarBackSize.x)* partyBackground->scale.x / 2 +0.01,
		UISizes::mainAvatarBackRedSize.y * mainBackground->scale.y + UISizes::partyBackgroundSize.y * partyBackground->scale.y / 2 + 0.04);


	// Magic ============
	magicBack = new SpriteNode(UISizes::magicBackSize);
	magicBack->texture = new Texture("/Resources/Game/UI/action_back.png");
	magicBack->scale = glm::vec2(winSize.y / UISizes::magicBackSize.y / 3);
	magicBack->position = glm::vec2(magicBack->scale.x*magicBack->size.x/2, 1 - magicBack->scale.y*magicBack->size.y /2);

	magicLarge = new MagicButton(magicBack,new Texture("/Resources/Game/UI/spell_99.png"), glm::vec2(1.0));
	magicLarge->setPosition(glm::vec2(0.3,0.7));
	magic1 = new MagicButton(magicBack, new Texture("/Resources/Game/UI/fire_3.png"), UISizes::magicIconSmallScale);
	magic1->setPosition(glm::vec2(0.3, 0.25));
	magic2 = new MagicButton(magicBack, new Texture("/Resources/Game/UI/fire_4.png"), UISizes::magicIconSmallScale);
	magic2->setPosition(glm::vec2(0.535, 0.35));
	magic3 = new MagicButton(magicBack, new Texture("/Resources/Game/UI/fire_10.png"), UISizes::magicIconSmallScale);
	magic3->setPosition(glm::vec2(0.63, 0.7));
	
	parentNode->addChildNode(magicBack);

	// bind magic -----------------
	
	




	// Enermy ============
	enBackground = new SpriteNode(UISizes::enBackgroundSize);
	enBackground->texture = new Texture("/Resources/Game/UI/background_en.png");
	enHpBar = new BarNode(enBackground, 100,
		new Texture("/Resources/Game/UI/hp_bar_en.png"),
		new Texture("/Resources/Game/UI/hp_bar_fade_en.png"),
		UISizes::enHpBarSize, UISizes::enHpFadeBarSize, id++);
	enAvatar = new SpriteNode(UISizes::avatarSize);
	enAvatar->texture = new Texture("/Resources/Game/UI/human_female.png");
	enAvatar->scale = glm::vec2(0.9);

	enAvatarBack = new SpriteNode(UISizes::enAvatarBackSize);
	enAvatarBack->texture = new Texture("/Resources/Game/UI/avatar_back_en.png");
	enAvatarBack->parentCoordinatePosition = glm::vec2(1-0.05, 0.5);

	enIcon = new SpriteNode(UISizes::avatarIconSize);
	enIcon->texture = new Texture("/Resources/Game/UI/spell_99.png");
	enIcon->parentCoordinatePosition = glm::vec2(1-0.72, 0.8);
	enIcon->scale = glm::vec2(0.2);
	
	enName = new TextNode(font, 0.45f, 3, 0.01f);
	enName->text = "Player Name";
	enName->scale = glm::vec2(0.1);
	enName->parentCoordinatePosition = glm::vec2(1 - 0.35, -0.05);

	if (isRed) {
		enAvatarTop = new SpriteNode(UISizes::enAvatarRedTopSize);
		enAvatarTop->texture = new Texture("/Resources/Game/UI/avatar_ver2_en_blue.png");
		enAvatarTop->parentCoordinatePosition = glm::vec2(0.26, 0.5);
	}
	else {
		enAvatarTop = new SpriteNode(UISizes::enAvatarBlueTopSize);
		enAvatarTop->texture = new Texture("/Resources/Game/UI/avatar_ver2_en_red.png");
		enAvatarTop->parentCoordinatePosition = glm::vec2(0.26, 0.5);
	}

	parentNode->addChildNode(enBackground);
	enBackground->addChildNode(enAvatarBack);
	enAvatarBack->renderingOrder = 2;
	enBackground->addChildNode(enName);
	enAvatarBack->addChildNode(enAvatar);
	enAvatarBack->addChildNode(enAvatarTop);
	enAvatarTop->addChildNode(enIcon);
	mainIcon->renderingOrder = 3;

	//---- en size ----
	enBackground->scale = glm::vec2(winSize.x / UISizes::enBackgroundSize.x / 4.5);
	enBackground->position = glm::vec2(winSize.x-((enBackground->size.x+enAvatarBack->size.x)
			*enBackground->scale.x/2 + winSize.x / 4),mainBackground->position.y);
	
	// setting ==================
}

void HUDNode::toggleEnermy(CharNode* chara)
{
	if (enBackground->isDisabled) {
		enHpBar->update(chara->health, engine);
		enName->text = chara->name;
		enBackground->isDisabled = false;
	}
	else {
		enBackground->isDisabled = true;
	}
}

void HUDNode::updateChar(CharNode* en)
{
	mainHpBar->update(selfChar->health, engine);
	mainMpBar->update(selfChar->stamina, engine);

	partyHpBar->update(ally->health, engine);
	partyMpBar->update(ally->stamina, engine);

	if (!enBackground->isDisabled) {
		enHpBar->update(en->health, engine);
	}
}
