#include "Logo.hpp"

#include <glm/gtc/random.hpp>

Logo::Logo(Engine* e, Font* font, UINode* parentNode, int* process)
{
	engine = e;
	this->font = font;
	isPlaying = false;
	pro = process;

	glm::vec2 winSize = glm::vec2(e->getWindowResolution().x / e->getWindowResolution().y, 1.0);
	background = new SpriteNode(winSize);
	background->color = glm::vec4(10.0f / 255.0f, 15.0f / 255.0f, 20.0f / 255.0f, 1.0f);
	background->screenPosition = glm::vec2(0.5);

	logoPic = new SpriteNode(glm::vec2(1));
	logoPic->texture = new Texture("/Resources/Game/UI/logo.png");
	logoPic->scale=glm::vec2(0.55f);
	logoPic->alpha = 0;

	logoBright = new SpriteNode(glm::vec2(1));
	logoBright->texture = new Texture("/Resources/Game/UI/logo_bright.png");
	logoBright->renderingOrder = 1;
	logoBright->alpha = 0;
    logoBright->setAdditive();

	light = new SpriteNode(glm::vec2(1));
	light->scale = glm::vec2(0);
	light->texture = new Texture("/Resources/Game/UI/logo_light.png");
	light->parentCoordinatePosition = glm::vec2(0.46,0.4);
    light->renderingOrder = 10;
	light->alpha = 0;
    light->rotation = 10.0f;
    light->setAdditive();
    
    lightSmall = new SpriteNode(glm::vec2(1));
    lightSmall->texture = new Texture("/Resources/Game/UI/logo_light_small.png");
    lightSmall->renderingOrder = 10;
    lightSmall->alpha = 0.5f;
    lightSmall->setAdditive();
    lightSmall->scale = glm::vec2(0.8f);
    light->addChildNode(lightSmall);
    
	nameBackground = new SpriteNode(UISizes::logoBackSize);
	nameBackground->texture = new Texture("/Resources/Game/UI/logo_back.png");
	nameBackground->alpha = 0;
	nameBackground->renderingOrder = 1;
	nameBackground->screenPosition = glm::vec2(0.5f, 0.48f);
    
    nameTop = new SpriteNode(glm::vec2(UISizes::logoBackSize.y));
    nameTop->texture = new Texture("/Resources/Game/UI/logo_top.png");
    nameTop->alpha = 0;
    nameTop->renderingOrder = 5;
    nameTop->setAdditive();
    nameBackground->addChildNode(nameTop);
    
    
    nameLight1 = new SpriteNode(glm::vec2(0.3f));
    nameLight1->texture = new Texture("/Resources/Game/UI/logo_light_small.png");
    nameLight1->renderingOrder = 2;
    nameLight1->alpha = 0.0f;
    nameLight1->setAdditive();
    nameLight1->position = glm::vec2(0.0f, -0.08f);
    nameBackground->addChildNode(nameLight1);
    
    nameLight2 = new SpriteNode(glm::vec2(0.3f));
    nameLight2->texture = new Texture("/Resources/Game/UI/logo_light_small.png");
    nameLight2->renderingOrder = 3;
    nameLight1->alpha = 0.0f;
    nameLight2->setAdditive();
    nameLight2->position = glm::vec2(0.0f, -0.08f);
    nameBackground->addChildNode(nameLight2);
    
    
    loadingText = new TextNode(font, 0.04f, 1.0f, 0.1f);
    loadingText->parentCoordinatePosition = glm::vec2(0.5, 0.66);
    loadingText->text = "Loading 0%";
    loadingText->color = Color::textColor;
    loadingText->alpha = 0.0f;
        
    loadingbar = new SpriteNode(glm::vec2(14.95f / 20.0f, 0.15f / 20.0f) * 1.2f);
    loadingbar->texture = new Texture("/Resources/Game/UI/loading.png");
    loadingbar->parentCoordinatePosition = glm::vec2(0.5, 0.7);
    loadingbar->renderingOrder = 1.0f;
    loadingbar->scale = glm::vec2(0, 1);
    loadingbar->alpha = 0.0f;

    background->addChildNode(loadingText);
    background->addChildNode(loadingbar);
    
    loadingbarBack = new SpriteNode(glm::vec2(16.0f / 20.0f, 1.0f / 20.0f) * 1.2f);
    loadingbarBack->texture = new Texture("/Resources/Game/UI/loading_back.png");
    loadingbarBack->parentCoordinatePosition = glm::vec2(0.5, 0.7);
    loadingbarBack->scale = glm::vec2(1, 1);
    loadingbarBack->alpha = 0.0f;
    background->addChildNode(loadingbarBack);
    
    
    loadingbarTop = new SpriteNode(glm::vec2(15.0f / 20.0f, 0.5f / 20.0f) * 1.2f);
    loadingbarTop->texture = new Texture("/Resources/Game/UI/loading_top.png");
    loadingbarTop->parentCoordinatePosition = glm::vec2(0.5, 0.7);
    loadingbarTop->scale = glm::vec2(1, 1);
    loadingbarTop->alpha = 0.0f;
    loadingbarTop->renderingOrder = 2.0f;
    background->addChildNode(loadingbarTop);
    
	parentNode->addChildNode(background);
	parentNode->addChildNode(nameBackground);
	background->addChildNode(logoPic);
	logoPic->addChildNode(logoBright);
	background->addChildNode(light);

	e->addNode(parentNode);
    
    Engine::main->loadMusic("logo music", new AudioBuffer("/Resources/Game/Sound/Logo.wav"));
}

void Logo::play() {
    
    Engine::main->playMusic("logo music");
    
    Animation* load = new Animation("loadlogo", 3.0f);
    load->setFloatAnimation(&logoPic->alpha, 1);
    load->setEaseOutTimingMode();
    engine->playAnimation(load);

    Animation* brightDelay = new Animation("brightDelay", 1.5f);
    brightDelay->setCompletionHandler([&] {
        Animation* bright = new Animation("logobright", 2.0f);
        bright->setEaseInTimingMode();
        bright->setFloatAnimation(&logoBright->alpha, 1);
        engine->playAnimation(bright);
    });
    engine->playAnimation(brightDelay);
    
    Animation* logoDeathDelay = new Animation("logoDeathDelay", 3.0f);
    logoDeathDelay->setCompletionHandler([&] {
        engine->stopAnimation("logobright");
        Animation* fade = new Animation("logofade", 0.5);
        fade->setEaseInTimingMode();
        fade->setFloatAnimation(&logoPic->alpha, 0);
        engine->playAnimation(fade);
    });
    engine->playAnimation(logoDeathDelay);
    
    Animation* lightWait = new Animation("lightWait", 2.5f);
    lightWait->setCompletionHandler([&] {
        
        Animation* lightRotation = new Animation("lightRotation", 3.0f);
        lightRotation->setFloatAnimation(&lightSmall->rotation, 360.0f);
        engine->playAnimation(lightRotation);
        
        Animation* lightRotation2 = new Animation("lightRotation2", 3.0f);
        lightRotation2->setFloatAnimation(&light->rotation, -30.0f);
        engine->playAnimation(lightRotation2);
        
        Animation* lightExpand = new Animation("lightExpand", 1.2);
        lightExpand->setVec2Animation(&light->scale, glm::vec2(1.5f));
        lightExpand->setEaseInTimingMode();
        engine->playAnimation(lightExpand);
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
        engine->playAnimation(shine);
    });
    engine->playAnimation(lightWait);
    
    Animation* loadingTextDelay = new Animation("loadingTextDelay", 3.5f);
    loadingTextDelay->setCompletionHandler([&] {
        
        Animation* loadtext = new Animation("loadText", 1.0f);
        loadtext->setEaseOutTimingMode();
        loadtext->setFloatAnimation(&nameBackground->alpha, 1.0f);
        loadtext->setCompletionHandler([&] {

            Animation* loadingTextDelay2 = new Animation("loadingTextDelay2", 2.0f);
            loadingTextDelay2->setCompletionHandler([&] {

                Animation* moveLoadText = new Animation("moveLoadText", 2.0f);
                moveLoadText->setEaseInEaseOutTimingMode();
                moveLoadText->setVec2Animation(&this->nameBackground->screenPosition, glm::vec2(0.5f, 0.38f));
                moveLoadText->setCompletionHandler([&] {

                    Animation* showLoadingbarTop = new Animation("showLoadingbarTop", 1.0f);
                    showLoadingbarTop->setEaseOutTimingMode();
                    showLoadingbarTop->setFloatAnimation(&this->loadingbarTop->alpha, 1.0f);
                    engine->playAnimation(showLoadingbarTop);

                    Animation* showLoadingbarBack = new Animation("showLoadingbarBack", 1.0f);
                    showLoadingbarBack->setEaseOutTimingMode();
                    showLoadingbarBack->setFloatAnimation(&this->loadingbarBack->alpha, 1.0f);
                    engine->playAnimation(showLoadingbarBack);

                    Animation* showLoadingText = new Animation("showLoadingText", 1.0f);
                    showLoadingText->setEaseOutTimingMode();
                    showLoadingText->setFloatAnimation(&this->loadingText->alpha, 1.0f);
                    engine->playAnimation(showLoadingText);

                    Animation* showLoadingBar = new Animation("showLoadingBar", 1.0f);
                    showLoadingBar->setEaseOutTimingMode();
                    showLoadingBar->setFloatAnimation(&this->loadingbar->alpha, 1.0f);
                    showLoadingBar->setCompletionHandler([&] {
                        *pro = 2;
                    });
                    engine->playAnimation(showLoadingBar);

                });
                engine->playAnimation(moveLoadText);
            });
            engine->playAnimation(loadingTextDelay2);

        });
        engine->playAnimation(loadtext);
        
    });
    engine->playAnimation(loadingTextDelay);
    
}

void Logo::updateLoad(float loadingProgess)
{
    
    if (!isPlaying) {
        int i = (int)(loadingProgess * 100);
        Animation* ani = new Animation("Loading" + std::to_string(i), 1.0f);
        float factor = loadingProgess;
        factor += glm::linearRand(0.0f, 0.1f);
        factor = glm::clamp(factor, 0.0f, 1.0f);
        ani->setVec2Animation(&loadingbar->scale, glm::vec2(factor, 1.0f));
        ani->setEaseInEaseOutTimingMode();
        engine->playAnimation(ani);
        isPlaying = true;
        ani->setCompletionHandler([&] {
            isPlaying = false;
            *pro = 3;
        });
    }
    
	if (loadingProgess >= 1) {
        
        *pro = -10;
        
        Animation* loadingTextDelay1 = new Animation("loadingTextDelay1", 1.0f);
        loadingTextDelay1->setCompletionHandler([&] {
            Animation* showLoadingbarTop = new Animation("showLoadingbarTop", 2.0f);
            showLoadingbarTop->setEaseOutTimingMode();
            showLoadingbarTop->setFloatAnimation(&this->loadingbarTop->alpha, 0.0f);
            engine->playAnimation(showLoadingbarTop);

            Animation* showLoadingbarBack = new Animation("showLoadingbarBack", 2.0f);
            showLoadingbarBack->setEaseOutTimingMode();
            showLoadingbarBack->setFloatAnimation(&this->loadingbarBack->alpha, 0.0f);
            engine->playAnimation(showLoadingbarBack);

            Animation* showLoadingText = new Animation("showLoadingText", 2.0f);
            showLoadingText->setEaseOutTimingMode();
            showLoadingText->setFloatAnimation(&this->loadingText->alpha, 0.0f);
            engine->playAnimation(showLoadingText);

            Animation* showLoadingBar = new Animation("showLoadingBar", 1.0f);
            showLoadingBar->setEaseOutTimingMode();
            showLoadingBar->setFloatAnimation(&this->loadingbar->alpha, 0.0f);
            engine->playAnimation(showLoadingBar);

        });
        engine->playAnimation(loadingTextDelay1);

        Animation* loadingTextDelay2 = new Animation("loadingTextDelay2", 2.0f);
        loadingTextDelay2->setCompletionHandler([&] {

            Animation* move = new Animation("titleMove", 2.0f);
            move->setFloatAnimation(&nameBackground->screenPosition.y, 0.25f);
            move->setEaseInEaseOutTimingMode();
            engine->playAnimation(move);

            Animation* changeScale = new Animation("titleScale", 2.0);
            changeScale->setVec2Animation(&nameBackground->scale, glm::vec2(0.9f));
            changeScale->setEaseInEaseOutTimingMode();
            engine->playAnimation(changeScale);

            Animation* end = new Animation("LoadEnd", 3.0f);
            end->setFloatAnimation(&background->alpha, 0.0f);
            end->setEaseInTimingMode();
            engine->playAnimation(end);

            *pro = 4;

        });
        engine->playAnimation(loadingTextDelay2);
		
	}
}

