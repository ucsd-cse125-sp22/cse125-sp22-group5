//
//  client-main.cpp
//
//  Created by Kangming Yu on 4/15/22.
//

#include <signal.h>

#include "Core/ClientCore/ClientCore.hpp"
#include "KGLEngine/Engine.hpp"
timeval* timepre = new timeval();
timeval* timecurr = new timeval();

void printtime(timeval* timecurr, timeval* timepre) {
    std::cout << (timecurr->tv_sec - timepre->tv_sec) * 1000000 + (timecurr->tv_usec - timepre->tv_usec) << std::endl;
}

#ifdef _WIN64
int gettimeofday(struct timeval* tp, void* tzp)
{
    time_t clock;
    struct tm tm;
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    tm.tm_year = wtm.wYear - 1900;
    tm.tm_mon = wtm.wMonth - 1;
    tm.tm_mday = wtm.wDay;
    tm.tm_hour = wtm.wHour;
    tm.tm_min = wtm.wMinute;
    tm.tm_sec = wtm.wSecond;
    tm.tm_isdst = -1;
    clock = mktime(&tm);
    tp->tv_sec = clock;
    tp->tv_usec = wtm.wMilliseconds * 1000;
    return (0);
}
#endif

#ifdef _WIN64
int gettimeofday(struct timeval* tp, void* tzp);
#endif

int main(int argc, char* argv[]) {
    if (signal(SIGINT, destructClientCore) == SIG_ERR) {
        perror("Signal_handler error");
        exit(1);
    }
    
    ClientCore::Instance()->initEngine();
    
    int cooldown = 10;
    SpriteNode* curtain = new SpriteNode(glm::vec2(10.0f));
    curtain->color = glm::vec4(10.0f / 255.0f, 15.0f / 255.0f, 20.0f / 255.0f, 1.0f);
    curtain->alpha = 1.0f;
    curtain->screenPosition = glm::vec2(0.5);
    curtain->renderingOrder = 10000000.0f;
    Engine::main->addNode(curtain);
    
    Engine::main->mainCameraNode = new CameraNode(60.0f, 0.1f, 10.0f);
    
    float frameTime = 0.0f;
    
    // Loading while
    while (Engine::main->isRunning()) {
        
        if(Engine::main->shouldUpdate()) {
            
            // Pre-loading --- process: 1
            if (ClientCore::Instance()->process() == 1) {
                ClientCore::Instance()->loadFont();
                ClientCore::Instance()->displayLogo();
                ClientCore::Instance()->set_process(0);
                
                Animation* curtainAnimation = new Animation("curtainAnimation", 3.0f);
                curtainAnimation->setFloatAnimation(&curtain->alpha, 0.0f);
                curtainAnimation->setEaseInEaseOutTimingMode();
                curtainAnimation->setCompletionHandler([&] {
                    ClientCore::Instance()->playLogo();
                });
                Engine::main->playAnimation(curtainAnimation);
            }
            
            // Loading display --- process: 2
            else if (ClientCore::Instance()->process() == 2) {
                ClientCore::Instance()->updateLoad();
                
                int progress = (int)((ClientCore::Instance()->logo_->loadingbar->scale.x + 0.01f) * 100);
                progress = glm::clamp(progress, 0, 100);
                ClientCore::Instance()->logo_->loadingText->text = "Loading " + std::to_string(progress) + "%";
                
            }
            
            // Loading --- process: 3
            else if (ClientCore::Instance()->process() == 3) {
                
                int progress = (int)((ClientCore::Instance()->logo_->loadingbar->scale.x + 0.01f) * 100);
                progress = glm::clamp(progress, 0, 100);
                ClientCore::Instance()->logo_->loadingText->text = "Loading " + std::to_string(progress) + "%";
                
                // Loading sky --- load_state: 1
                if (ClientCore::Instance()->load_state() == 1) {
                    ClientCore::Instance()->loadSky();
                }
                // Loading light --- load_state: 2
                else if (ClientCore::Instance()->load_state() == 2) {
                    ClientCore::Instance()->loadLight();
                }
                // Loading Map --- load_state: 3
                else if (ClientCore::Instance()->load_state() == 3) {
                    ClientCore::Instance()->loadMap();
                }
                // Loading Character --- load_state: 4
                else if (ClientCore::Instance()->load_state() == 4) {
                    ClientCore::Instance()->loadCharacter();
                }
                // Loading Magic --- load_state: 5
                else if (ClientCore::Instance()->load_state() == 5) {
                    ClientCore::Instance()->loadMagic();
                }
                // Loading Damage System --- load_state: 6
                else if (ClientCore::Instance()->load_state() == 6) {
                    ClientCore::Instance()->loadDamageSystem();
                }
                // Loading Start Scene --- load_state: 7
                else if (ClientCore::Instance()->load_state() == 7) {
                    ClientCore::Instance()->loadStartScene();
                }
                // Loading Death Scene --- load_state: 8
                else if (ClientCore::Instance()->load_state() == 8) {
                    ClientCore::Instance()->loadDeathScene();
                }
                // Loading End
                else {
                    ClientCore::Instance()->set_process(2);
                    break;
                }
            }
            else if (ClientCore::Instance()->process() == -10) {
                
                int progress = (int)((ClientCore::Instance()->logo_->loadingbar->scale.x + 0.01f) * 100);
                progress = glm::clamp(progress, 0, 100);
                ClientCore::Instance()->logo_->loadingText->text = "Loading " + std::to_string(progress) + "%";
                
            }
            // Render
            if(ClientCore::Instance()->logo_ != nullptr) {
                if(ClientCore::Instance()->logo_->nameTop != nullptr) {
                    frameTime += 1.0f / 60.0f;
                    ClientCore::Instance()->logo_->nameTop->alpha = 0.5f - glm::sin(frameTime * 2.0f) * 0.25f;
                    ClientCore::Instance()->logo_->nameLight1->alpha = glm::sin(frameTime * 2.0f) * 0.1f + 0.2f;
                    ClientCore::Instance()->logo_->nameLight2->alpha = glm::cos(frameTime) * 0.1f + 0.2f;
                    ClientCore::Instance()->logo_->nameLight1->rotation += 0.5f;
                    ClientCore::Instance()->logo_->nameLight2->rotation -= 1.0f;
                }
            }
            Engine::main->render();
            cooldown -= 1;
            if (ClientCore::Instance()->process() == -1 && cooldown <= 0) {
                ClientCore::Instance()->set_process(1);
            }
            
            
            
        }
    }
    
    Engine::main->input->wasKeyPressed(MOUSE_BUTTON_LEFT);
    Engine::main->input->wasKeyReleased(MOUSE_BUTTON_LEFT);
    Engine::main->input->wasKeyPressed(KEY_SPACE);
    Engine::main->input->wasKeyPressed(KEY_G);
    Engine::main->input->wasKeyPressed(KEY_C);
    Engine::main->input->wasKeyPressed(KEY_1);
    Engine::main->input->wasKeyPressed(KEY_2);
    Engine::main->input->wasKeyPressed(KEY_3);
    Engine::main->input->wasKeyPressed(KEY_4);
    
    
    // Pre-Game while
    while(Engine::main->isRunning()) {
        if(Engine::main->shouldUpdate()) {
            // Start Scene --- process: 4
            if (ClientCore::Instance()->process() == 4) {
                ClientCore::Instance()->displayStart();
            }
            else if (ClientCore::Instance()->process() == 5) {
                ClientCore::Instance()->updateStart();
            }
            else if (ClientCore::Instance()->process() == 6) {
                ClientCore::Instance()->playCG();
            }
            else if (ClientCore::Instance()->process() == 7) {
                ClientCore::Instance()->set_process(8);
                break;
            }
            
            Engine::main->input->wasKeyPressed(MOUSE_BUTTON_LEFT);
            Engine::main->input->wasKeyReleased(MOUSE_BUTTON_LEFT);
            Engine::main->input->wasKeyPressed(KEY_SPACE);
            Engine::main->input->wasKeyPressed(KEY_G);
            Engine::main->input->wasKeyPressed(KEY_C);
            Engine::main->input->wasKeyPressed(KEY_1);
            Engine::main->input->wasKeyPressed(KEY_2);
            Engine::main->input->wasKeyPressed(KEY_3);
            Engine::main->input->wasKeyPressed(KEY_4);
            
            frameTime += Engine::main->getDeltaTime();
            if(ClientCore::Instance()->logo_ != nullptr) {
                if(ClientCore::Instance()->logo_->nameTop != nullptr) {
                    frameTime += 1.0f / 60.0f;
                    ClientCore::Instance()->logo_->nameTop->alpha = 0.5f - glm::sin(frameTime * 2.0f) * 0.25f;
                    ClientCore::Instance()->logo_->nameLight1->alpha = glm::sin(frameTime * 2.0f) * 0.1f + 0.2f;
                    ClientCore::Instance()->logo_->nameLight2->alpha = glm::cos(frameTime) * 0.1f + 0.2f;
                    ClientCore::Instance()->logo_->nameLight1->rotation += 0.5f;
                    ClientCore::Instance()->logo_->nameLight2->rotation -= 1.0f;
                }
            }
            ClientCore::Instance()->renderWorld();
        }
    }
    
    Engine::main->input->wasKeyPressed(MOUSE_BUTTON_LEFT);
    Engine::main->input->wasKeyReleased(MOUSE_BUTTON_LEFT);
    Engine::main->input->wasKeyPressed(KEY_SPACE);
    Engine::main->input->wasKeyPressed(KEY_G);
    Engine::main->input->wasKeyPressed(KEY_C);
    Engine::main->input->wasKeyPressed(KEY_1);
    Engine::main->input->wasKeyPressed(KEY_2);
    Engine::main->input->wasKeyPressed(KEY_3);
    Engine::main->input->wasKeyPressed(KEY_4);
    
    float time;
    while (true) {
        if (ClientCore::Instance()->process() == 8 && Engine::main->shouldUpdate()) {
            ClientCore::Instance()->handleEvent();
            
            ClientCore::Instance()->sendData();
            
            ClientCore::Instance()->renderWorld();

            ClientCore::Instance()->receiveData();
            
            ClientCore::Instance()->updateState();
            time = Engine::main->getTime();

            std::cout << "render time: " << Engine::main->getTime() - time << std::endl;
            std::cout << "fps: " << Engine::main->getCurrentFPS() << std::endl;
        }
        else if (ClientCore::Instance()->process() == 9) {
            ClientCore::Instance()->set_process(10);
            break;
        }
    }
    
    
    // Post-Game while
    while(Engine::main->isRunning()) {
        if(Engine::main->shouldUpdate()) {
            
            if (ClientCore::Instance()->process() == 10) {
                ClientCore::Instance()->resetGame();
            }
            ClientCore::Instance()->renderWorld();
        }
    }
    
    return 0;
}
