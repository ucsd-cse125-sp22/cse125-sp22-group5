#include "Logo.hpp"

Logo::Logo(Engine* e, Font* font, UINode* parentNode, int* process)
{
	engine = e;
	this->font = font;
	isload = false;
	isPlaying = false;
	pro = process;

	glm::vec2 winSize = glm::vec2(e->getWindowResolution().x / e->getWindowResolution().y, 1.0);
	background = new SpriteNode(winSize);
	background->color = glm::vec4(0,0,0,1);
	background->screenPosition = glm::vec2(0.5);

	logoPic = new SpriteNode(glm::vec2(1));
	logoPic->texture = new Texture("/Resources/Game/UI/logo.png");
	logoPic->scale=glm::vec2(0.55f);
    
	logoPic->alpha = 0;

	light = new SpriteNode(glm::vec2(1));
	light->scale = glm::vec2(0);
	light->texture = new Texture("/Resources/Game/UI/logo_light.png");
	light->parentCoordinatePosition = glm::vec2(0.46,0.4);
	light->alpha = 0;

	nameBackground = new SpriteNode(UISizes::logoBackSize);
	nameBackground->texture = new Texture("/Resources/Game/UI/logo_back.png");
	nameBackground->alpha = 0;
	nameBackground->renderingOrder = 1;
	nameBackground->screenPosition = glm::vec2(0.5,0.4);

	name = new TextNode(font,0.15f,1.0f,0.1f);
	name->text = "Eternal Ritual";
	name->color = Color::LogotextColor;
	name->parentCoordinatePosition = glm::vec2(0.5,0.69);

	parentNode->addChildNode(background);
	parentNode->addChildNode(nameBackground);
	nameBackground->addChildNode(name);
	background->addChildNode(logoPic);
	background->addChildNode(light);

	e->addNode(parentNode);

}

void Logo::play() {

	Animation* lightWait = new Animation("lightWait", 2.8);
	lightWait->setCompletionHandler([&] {

		Animation* lightExpand = new Animation("lightExpand", 1.2);
		lightExpand->setVec2Animation(&light->scale, glm::vec2(2.7));
		lightExpand->setEaseInTimingMode();


		Animation* shine = new Animation("logoShine", 0.5);
		shine->setFloatAnimation(&light->alpha, 1);
		shine->setEaseInTimingMode();
		shine->setCompletionHandler([&] {
			Animation* delay = new Animation("shinedelay", 0.4);
			delay->setCompletionHandler([&] {

				Animation* lightFade = new Animation("lightFade", 0.3);
				lightFade->setFloatAnimation(&light->alpha, 0);
				lightFade->setEaseOutTimingMode();
				engine->playAnimation(lightFade);
			});
			engine->playAnimation(delay);
		});
		engine->playAnimation(lightExpand);
		engine->playAnimation(shine);
	});

	Animation* load = new Animation("loadlogo", 1.5);
	load->setFloatAnimation(&(logoPic->alpha), 1);
	load->setEaseInTimingMode();
	load->setCompletionHandler([&] {	
		Animation* delay = new Animation("logodelay", 2);
		delay->setCompletionHandler([&] {
			Animation* fade = new Animation("logofade", 0.5);
			fade->setEaseOutTimingMode();
			fade->setFloatAnimation(&(logoPic->alpha), 0);
			fade->setCompletionHandler([&] {
				Animation* loadtext = new Animation("loadText",0.7);
				loadtext->setEaseInTimingMode();
				loadtext->setFloatAnimation(&nameBackground->alpha, 1);
				loadtext->setCompletionHandler([&] {
					*pro = 2;
				});
				engine->playAnimation(loadtext);
			});
			engine->playAnimation(fade);
		});
		engine->playAnimation(delay);
	});

	engine->playAnimation(lightWait);
	engine->playAnimation(load);

}

void Logo::updateLoad(float loadingProgess)
{
	if (!isload) {
		loadingText = new TextNode(font, 0.05f, 1.0f, 0.1f);
		loadingText->parentCoordinatePosition = glm::vec2(0.5, 0.7);
		loadingText->text = "Loading 0%";
		loadingText->color = Color::textColor;
		
		loadingbar = new SpriteNode(glm::vec2(engine->getWindowResolution().x / engine->getWindowResolution().y - 0.2, 0.01));
		loadingbar->color = Color::loadingBarColor;
		loadingbar->parentCoordinatePosition = glm::vec2(0.5, 0.75);
		loadingbar->scale = glm::vec2(0, 1);

		background->addChildNode(loadingText);
		background->addChildNode(loadingbar);

		isload = true;
		*pro = 3;
	}
	else {
        loadingText->text = "Loading " + std::to_string((int)((loadingbar->scale.x + 0.01) * 100)) + "%";
        if (!isPlaying) {
            int i = (int)(loadingProgess * 100);
            Animation* ani = new Animation(std::to_string(i), 1);
            ani->setVec2Animation(&loadingbar->scale, glm::vec2(loadingProgess, 1));
            engine->playAnimation(ani);
            isPlaying = true;
            ani->setCompletionHandler([&] {
            isPlaying = false;
            *pro = 3;
           });
        }
	}
	if (loadingProgess >= 1) {
		Animation* end = new Animation("LoadEnd", 1.0);
		end->setFloatAnimation(&background->alpha, 0);
		end->setCompletionHandler([&] {
			background->isDisabled = true;
			Animation* move = new Animation("titleMove", 1.0);
			move->setFloatAnimation(&nameBackground->screenPosition.y, 0.25);
			move->setEaseInEaseOutTimingMode();
			Animation* changeScale = new Animation("titleScale", 1.0);
			changeScale->setVec2Animation(&nameBackground->scale, glm::vec2(0.9));
			engine->playAnimation(move);
			engine->playAnimation(changeScale);
			*pro = 4;
		});
		engine->playAnimation(end);
	}
}

