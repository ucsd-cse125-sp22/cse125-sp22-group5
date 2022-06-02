#include "Game/UI/HUDNode.hpp"

#include <iostream>
#include <glm/glm.hpp>

#include "Game/UI/Constant.hpp"


void HUDNode::selectMagic()
{
	switch (selfChar->currMagic)
	{
	case 0:
		magicLarge->toggleSelect(false);
		magic1->toggleSelect(true);
		magic2->toggleSelect(false);
		magic3->toggleSelect(false);
		break;
	case 1:
		magicLarge->toggleSelect(false);
		magic1->toggleSelect(false);
		magic2->toggleSelect(true);
		magic3->toggleSelect(false);
		break;
	case 2:
		magicLarge->toggleSelect(false);
		magic1->toggleSelect(false);
		magic2->toggleSelect(false);
		magic3->toggleSelect(true);
		break;
	case 3:
		magicLarge->toggleSelect(true);
		magic1->toggleSelect(false);
		magic2->toggleSelect(false);
		magic3->toggleSelect(false);
		break;
	default:
		magicLarge->toggleSelect(true);
		magic1->toggleSelect(false);
		magic2->toggleSelect(false);
		magic3->toggleSelect(false);
		break;
	}
}

HUDNode::HUDNode(Engine* e, UINode* parentNode, bool isRed, Font* font, CharNode* selfChar, CharNode* ally)
{
	engine = e;
	this->parentNode = parentNode;
	this->selfChar = selfChar;
	this->ally = ally;
	glm::vec2 winSize = glm::vec2(engine->getWindowResolution().x/engine->getWindowResolution().y,1.0);
	int id = 0;

	// Main =========================
	leftBack = new SpriteNode(UISizes::leftBackSize);
	leftBack->texture = new Texture("/Resources/Game/UI/left_back.png");
	leftBack->scale = glm::vec2(winSize.x / UISizes::leftBackSize.x/4);
	leftBack->position = glm::vec2(leftBack->scale.x * leftBack->size.x / 2,
		leftBack->scale.y * leftBack->size.y / 2);
	parentNode->addChildNode(leftBack);
	leftBack->alpha = 0.8;

	mainBackground = new SpriteNode(UISizes::mainBackgroundSize);
	mainBackground->texture = new Texture("/Resources/Game/UI/background_main.png");
	mainHpBar = new BarNode(mainBackground,selfChar->health,
		new Texture("/Resources/Game/UI/hp_bar_main.png"),
		new Texture("/Resources/Game/UI/hp_bar_fade_main.png"),
		UISizes::mainHpBarSize, UISizes::mainHpFadeBarSize, id++, true, engine);
	mainHpBar->setPosition(glm::vec2(0.5,0.32));
	mainMpBar = new BarNode(mainBackground, selfChar->mana,
		new Texture("/Resources/Game/UI/mp_bar_main.png"),
		new Texture("/Resources/Game/UI/mp_bar_fade_main.png"),
		UISizes::mainMpBarSize, UISizes::mainMpFadeBarSize, id++, true, engine);
	mainMpBar->setPosition(glm::vec2(0.44,0.75));
	mainAvatar = new SpriteNode(UISizes::avatarSize);
	mainAvatar->texture = new Texture("/Resources/Game/UI/human_female.png");
	mainName = new TextNode(font, 0.45f, 3, 0.01f);
	mainName->text = selfChar->name;
	mainName->scale = glm::vec2(0.11);
	mainName->parentCoordinatePosition = glm::vec2(0.29,-0.13);
	
	if (isRed) {
		mainAvatar->parentCoordinatePosition = glm::vec2(0.118, 0.5);
		mainAvatarBack = new SpriteNode(UISizes::mainAvatarBackRedSize);
		mainAvatarBack->texture = new Texture("/Resources/Game/UI/avatar_back_red.png");
		mainAvatarTop = new SpriteNode(UISizes::mainAvatarRedTopSize);
		mainAvatarTop->texture = new Texture("/Resources/Game/UI/avatar_ver2_red.png");
		mainAvatarTop->parentCoordinatePosition = glm::vec2(0.155, 0.5);
		mainIcon = new SpriteNode(UISizes::avatarIconSize);
		mainIcon->texture = new Texture("/Resources/Game/UI/icon_red.png");
		mainIcon->parentCoordinatePosition = glm::vec2(0.72, 0.8);
		mainIcon->scale = UISizes::avatarIconScale;
	}
	else {
		mainAvatar->parentCoordinatePosition = glm::vec2(0.231, 0.5);
		mainAvatarBack = new SpriteNode(UISizes::mainAvatarBackBlueSize);
		mainAvatarBack->texture = new Texture("/Resources/Game/UI/avatar_back_blue.png");
		mainAvatarBack->parentCoordinatePosition = glm::vec2(0.335,0.5);
		mainAvatarTop = new SpriteNode(UISizes::mainAvatarBlueTopSize);
		mainAvatarTop->texture = new Texture("/Resources/Game/UI/avatar_ver2_blue.png");
		mainAvatarTop->parentCoordinatePosition = glm::vec2(0.27, 0.5);
		mainIcon = new SpriteNode(UISizes::avatarIconSize);
		mainIcon->texture = new Texture("/Resources/Game/UI/icon_blue.png");
		mainIcon->parentCoordinatePosition = glm::vec2(0.72, 0.8);
		mainIcon->scale = UISizes::avatarIconScale;
	}

	//parentNode->addChildNode(mainBackground);
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
	partyHpBar = new BarNode(partyBackground, ally->health,
		new Texture("/Resources/Game/UI/hp_bar_party.png"),
		new Texture("/Resources/Game/UI/hp_bar_fade_party.png"),
		UISizes::partyHpBarSize, UISizes::partyHpFadeBarSize, id++, true, engine);
	partyHpBar->setPosition(glm::vec2(0.5, 0.32));
	partyMpBar = new BarNode(partyBackground, ally->mana,
		new Texture("/Resources/Game/UI/mp_bar_party.png"),
		new Texture("/Resources/Game/UI/mp_bar_fade_party.png"),
		UISizes::partyMpBarSize, UISizes::partyMpFadeBarSize, id++, true, engine);
	partyMpBar->setPosition(glm::vec2(0.44, 0.75));
	partyAvatar = new SpriteNode(UISizes::avatarSize);
	partyAvatar->texture = new Texture("/Resources/Game/UI/human_female.png");
	partyAvatarBack = new SpriteNode(UISizes::partyAvatarBackSize);
	partyAvatarBack->texture = new Texture("/Resources/Game/UI/avatar_back_party.png");
	partyAvatarBack->parentCoordinatePosition = glm::vec2(0.05,0.5);
	partyName = new TextNode(font, 0.45f, 3, 0.01f);
	partyName->text = ally->name;
	partyName->scale = glm::vec2(0.1,0.2);
	partyName->parentCoordinatePosition = glm::vec2(0.36, -0.1);

	if (isRed) {
		partyIcon = new SpriteNode(UISizes::avatarIconSize);
		partyIcon->texture = new Texture("/Resources/Game/UI/icon_red.png");
		partyIcon->parentCoordinatePosition = glm::vec2(0.72, 0.8);
		partyIcon->scale = UISizes::avatarIconScale;
		partyAvatarTop = new SpriteNode(UISizes::partyAvatarRedTopSize);
		partyAvatarTop->texture = new Texture("/Resources/Game/UI/avatar_ver2_party_red.png");
		partyAvatarTop->parentCoordinatePosition = glm::vec2(0.7, 0.5);
	}
	else {
		partyIcon = new SpriteNode(UISizes::avatarIconSize);
		partyIcon->texture = new Texture("/Resources/Game/UI/icon_blue.png");
		partyIcon->parentCoordinatePosition = glm::vec2(0.72, 0.8);
		partyIcon->scale = UISizes::avatarIconScale;
		partyAvatarTop = new SpriteNode(UISizes::partyAvatarBlueTopSize);
		partyAvatarTop->texture = new Texture("/Resources/Game/UI/avatar_ver2_party_blue.png");
		partyAvatarTop->parentCoordinatePosition = glm::vec2(0.7, 0.5);
	}

	UINode* placehold = new UINode();

	//parentNode->addChildNode(placehold);
	//parentNode->addChildNode(partyBackground);

	placehold->addChildNode(partyAvatarBack);
	partyAvatarBack->renderingOrder = 2;
	partyBackground->addChildNode(partyName);
	partyAvatarBack->addChildNode(partyAvatar);
	partyAvatarBack->addChildNode(partyAvatarTop);
	partyAvatarTop->addChildNode(partyIcon);
	partyIcon->renderingOrder = 3;

	//---- party size ----
	partyBackground->scale = glm::vec2(winSize.x / UISizes::partyBackgroundSize.x / 5.5,
		winSize.x / UISizes::partyBackgroundSize.x / 5.5 /2);
	partyBackground->position = glm::vec2((UISizes::partyBackgroundSize.x + UISizes::partyAvatarBackSize.x)* partyBackground->scale.x / 2 +0.01,
		UISizes::mainAvatarBackRedSize.y * mainBackground->scale.y + UISizes::partyBackgroundSize.y * partyBackground->scale.y / 2 + 0.04);
	placehold->scale = glm::vec2(partyBackground->scale.x*0.9, partyBackground->scale.y* 0.9 *2);
	//placehold->position = glm::vec2((UISizes::partyAvatarBackSize.x) * placehold->scale.x / 2 + 0.03,partyBackground->position.y);
	placehold->position = glm::vec2( partyBackground->position.x - UISizes::partyBackgroundSize.x * partyBackground->scale.x/2 + 0.02
		,partyBackground->position.y);
	

	// Enermy ============
	enBackground = new SpriteNode(UISizes::enBackgroundSize);
	enBackground->texture = new Texture("/Resources/Game/UI/background_en.png");
	enHpBar = new BarNode(enBackground, selfChar->health,
		new Texture("/Resources/Game/UI/hp_bar_en.png"),
		new Texture("/Resources/Game/UI/hp_bar_fade_en.png"),
		UISizes::enHpBarSize, UISizes::enHpFadeBarSize, id++, false, engine);
	enAvatar = new SpriteNode(UISizes::avatarSize);
	enAvatar->texture = new Texture("/Resources/Game/UI/human_female.png");
	enAvatar->scale = glm::vec2(0.9);

	enAvatarBack = new SpriteNode(UISizes::enAvatarBackSize);
	enAvatarBack->texture = new Texture("/Resources/Game/UI/avatar_back_en.png");
	enAvatarBack->parentCoordinatePosition = glm::vec2(1 - 0.05, 0.5);

	enName = new TextNode(font, 0.45f, 3, 0.01f);
	enName->scale = glm::vec2(0.1);
	enName->parentCoordinatePosition = glm::vec2(1 - 0.35, -0.05);

	if (isRed) {
		enIcon = new SpriteNode(UISizes::avatarIconSize);
		enIcon->texture = new Texture("/Resources/Game/UI/icon_blue.png");
		enIcon->parentCoordinatePosition = glm::vec2(1 - 0.72, 0.8);
		enIcon->scale = UISizes::avatarIconScale;
		enAvatarTop = new SpriteNode(UISizes::enAvatarRedTopSize);
		enAvatarTop->texture = new Texture("/Resources/Game/UI/avatar_ver2_en_blue.png");
		enAvatarTop->parentCoordinatePosition = glm::vec2(0.26, 0.5);
	}
	else {
		enIcon = new SpriteNode(UISizes::avatarIconSize);
		enIcon->texture = new Texture("/Resources/Game/UI/icon_red.png");
		enIcon->parentCoordinatePosition = glm::vec2(1 - 0.72, 0.8);
		enIcon->scale = UISizes::avatarIconScale;
		enAvatarTop = new SpriteNode(UISizes::enAvatarBlueTopSize);
		enAvatarTop->texture = new Texture("/Resources/Game/UI/avatar_ver2_en_red.png");
		enAvatarTop->parentCoordinatePosition = glm::vec2(0.26, 0.5);
	}

	//parentNode->addChildNode(enBackground);
	enBackground->addChildNode(enAvatarBack);
	enAvatarBack->renderingOrder = 2;
	enBackground->addChildNode(enName);
	enAvatarBack->addChildNode(enAvatar);
	enAvatarBack->addChildNode(enAvatarTop);
	enAvatarTop->addChildNode(enIcon);
	enIcon->renderingOrder = 3;
	enBackground->isDisabled = true;

	//---- en size ----
	enBackground->scale = glm::vec2(winSize.x / UISizes::enBackgroundSize.x / 4.5);
	enBackground->position = glm::vec2(winSize.x - ((enBackground->size.x + enAvatarBack->size.x)
		* enBackground->scale.x / 2), mainBackground->position.y);



	// Magic ============
	magicBack = new SpriteNode(UISizes::magicBackSize);
	magicBack->texture = new Texture("/Resources/Game/UI/action_back.png");
	magicBack->scale = glm::vec2(winSize.y / UISizes::magicBackSize.y / 3.5);
	magicBack->position = glm::vec2(magicBack->scale.x*magicBack->size.x/2, 1 - magicBack->scale.y*magicBack->size.y /2);

	magicLarge = new MagicButton(magicBack,new Texture("/Resources/Game/UI/beast_44.png"), UISizes::magicIconLargeScale,selfChar->magics[3]);
	magicLarge->setPosition(glm::vec2(0.3,0.7));
	magic1 = new MagicButton(magicBack, new Texture("/Resources/Game/UI/fire_4.png"), UISizes::magicIconSmallScale, selfChar->magics[0]);
	magic1->setPosition(glm::vec2(0.3, 0.27));
	magic2 = new MagicButton(magicBack, new Texture("/Resources/Game/UI/blazing_51.png"), UISizes::magicIconSmallScale, selfChar->magics[1]);
	magic2->setPosition(glm::vec2(0.615, 0.4));
	magic3 = new MagicButton(magicBack, new Texture("/Resources/Game/UI/blazing_11.png"), UISizes::magicIconSmallScale, selfChar->magics[2]);
	magic3->setPosition(glm::vec2(0.75, 0.72));

	selectMagic();
	
	//parentNode->addChildNode(magicBack);
	
	// Tutorial ==================
	UINode* listBack = new UINode();
	listTop = new SpriteNode(UISizes::listHeadBackSize);
	listTop->texture = new Texture("/Resources/Game/UI/listTopBack.png");
	listBottom = new SpriteNode(UISizes::listHeadBackSize);
	listBottom->texture = new Texture("/Resources/Game/UI/listBottomBack.png");
	float height = 0.022;
	float length = UISizes::listHeadBackSize.x - 0.03;
	float distance = 0.004f;
	tutorialText = new TextNode(font, height, length, distance);
	tutorialText->text = "Movement: w/s/a/d \n Roll: space\nLock Enermy: F\n Acttack: mouse left\n Select magic: mouse middle";
	tutorialText->setLeftHorizontalAlignment();
	tutorialText->color = Color::textColor;
	TextNode* title = new TextNode(font, height, length, distance);
	title->text = "Tutorial";
	title->setCenterVerticalAlignment();
	title->color = Color::textColor;

	float textY = 4 * (height + distance);

	SpriteNode* listBackground = new SpriteNode(glm::vec2(UISizes::listHeadBackSize.x, 
		listTop->size.y + listBottom->size.y + textY));
	listBackground->texture = new Texture("/Resources/Game/UI/list_back.png");
	listBackground->parentCoordinatePosition = glm::vec2(0.5);
	listBackground->alpha = 0.8;

	listBack->addChildNode(listBackground);
	listBack->addChildNode(listTop);
	listBack->addChildNode(listBottom);
	listBack->addChildNode(tutorialText);
	listTop->addChildNode(title);

	listBack->size = listBackground->size;
	listTop->parentCoordinatePosition = glm::vec2(0.5, 0);
	tutorialText->parentCoordinatePosition = glm::vec2(0.01,0.5);
	listBottom->parentCoordinatePosition = glm::vec2(0.5,1);
	
	listBack->scale = glm::vec2(1);
	listBack->position = glm::vec2(winSize.x - UISizes::listHeadBackSize.x/2,winSize.y-(listBack->size.y/2 + UISizes::listHeadBackSize.y + 0.01));
	//parentNode->addChildNode(listBack);

	// Notification
	viewBack = new SpriteNode(UISizes::viewBackSize);
	viewBack->texture = new Texture("/Resources/Game/UI/notification_back.png");
	viewText = new TextNode(font,0.05,1,0.1);
	viewText->text = ally->name + "'s view";
	viewText->parentCoordinatePosition = glm::vec2(0.5,0.73);
	viewBack->screenPosition = glm::vec2(0.5, 0.2);
	viewBack->addChildNode(viewText);
	viewBack->alpha = 0;

	deathBack = new SpriteNode(UISizes::deathBackSize);
	deathBack->texture = new Texture("/Resources/Game/UI/death_back.png");
	deathText = new TextNode(font, 0.08, 1, 0.1);
	deathText->text = "You Dead";
	deathText->parentCoordinatePosition = glm::vec2(0.5, 0.65);
	deathText->color = Color::textColor;
	deathBack->screenPosition = glm::vec2(0.5, 0.75);
	deathBack->addChildNode(deathText);
	deathBack->alpha = 0;
	deathBack->isDisabled = true;
	deathBack->scale = glm::vec2(0, 1);

	aliveBase = new UINode();
	aliveBase->addChildNode(mainBackground);
	aliveBase->addChildNode(enBackground);
	aliveBase->addChildNode(magicBack);
	aliveBase->addChildNode(listBack);
	aliveBase->addChildNode(partyBackground);
	aliveBase->addChildNode(placehold);

	parentNode->addChildNode(aliveBase);
	parentNode->addChildNode(viewBack);
	parentNode->addChildNode(deathBack);
}

void HUDNode::update(bool viewAlly)
{
	mainHpBar->update(selfChar->health);
	mainMpBar->update(selfChar->mana);

	partyHpBar->update(ally->health);
	partyMpBar->update(ally->mana);

	// Character
	if (selfChar->health <= 0) {
		deathBack->isDisabled = false;
		viewBack->isDisabled = false;
		Animation* death = new Animation("showDeath", 0.3);
		death->setFloatAnimation(&deathBack->alpha, 1);
		//death->setEaseInEaseOutTimingMode();
		Animation* deathWidth = new Animation("showDeathWidth", 0.3);
		deathWidth->setFloatAnimation(&deathBack->scale.x, 1);
		//deathWidth->setEaseInEaseOutTimingMode();
		Animation* view = new Animation("showViewDead", 0.1);
		view->setFloatAnimation(&viewBack->alpha, 1);
		view->setEaseInEaseOutTimingMode();
		Animation* back = new Animation("deBack", 0.1);
		back->setFloatAnimation(&aliveBase->alpha, 0);
		back->setEaseInEaseOutTimingMode();
		engine->playAnimation(view);
		engine->playAnimation(death);
		engine->playAnimation(deathWidth);
		engine->playAnimation(back);
	}
	else {

		if (viewAlly) {
			Animation* view = new Animation("showView", 0.1);
			view->setFloatAnimation(&viewBack->alpha, 1);
			view->setEaseInEaseOutTimingMode();
			engine->playAnimation(view);
		}
		else {
			Animation* DiView = new Animation("dishowView", 0.1);
			DiView->setFloatAnimation(&viewBack->alpha, 0);
			DiView->setEaseInEaseOutTimingMode();
			engine->playAnimation(DiView);
		}

		if (selfChar->isLocked) {
			enBackground->isDisabled = false;
			enName->text = selfChar->target->name;
			enHpBar->update(selfChar->target->health);
		}
		else {
			enBackground->isDisabled = true;
		}

		// Magic
		float mpleft = selfChar->mana;
		selectMagic();
		magicLarge->setProgess(mpleft);
		magic1->setProgess(mpleft);
		magic2->setProgess(mpleft);
		magic3->setProgess(mpleft);

	}
	
}

void HUDNode::toggleViewDead(CharNode* name)
{
	viewText->text = name->name + "'s View";
}

void HUDNode::reset() {
	viewBack->isDisabled = true;
	deathBack->isDisabled = true;
	deathBack->scale = glm::vec2(0, 1);
	engine->stopAnimation("showDeathWidth");
	engine->stopAnimation("showDeath");
	engine->stopAnimation("deBack");
	aliveBase->isDisabled = false;
	aliveBase->alpha = 1;
}
