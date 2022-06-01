//
//  client-main.cpp
//
//  Created by Kangming Yu on 4/15/22.
//

#include <signal.h>

#include "Core/ClientCore/ClientCore.hpp"
#include "KGLEngine/Engine.hpp"


int main(int argc, char* argv[]) {
    if (signal(SIGINT, destructClientCore) == SIG_ERR) {
        perror("Signal_handler error");
        exit(1);
    }
    
    ClientCore::Instance()->initEngine();
    
    // Loading while
    while (Engine::main->isRunning()) {
        if (Engine::main->input->wasKeyReleased(KEY_ESCAPE)) {
            exit(1);
        }
        
        if(Engine::main->shouldUpdate()) {
            // Pre-loading --- process: 1
            if (ClientCore::Instance()->process() == 1) {
                ClientCore::Instance()->loadFont();
                ClientCore::Instance()->displayLogo();
                ClientCore::Instance()->set_process(0);
            }
            
            // Loading display --- process: 2
            else if (ClientCore::Instance()->process() == 2) {
                ClientCore::Instance()->updateLoad();
            }
            
            // Loading --- process: 3
            else if (ClientCore::Instance()->process() == 3) {
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
                    ClientCore::Instance()->set_process(4);
                    break;
                }
            }
            // Render
            Engine::main->render();
        }
    }
    
    
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
            ClientCore::Instance()->renderWorld();
        }
    }
    
    
    while (true) {
        if (ClientCore::Instance()->process() == 8) {
            ClientCore::Instance()->handleEvent();
            
            ClientCore::Instance()->sendData();
            
            ClientCore::Instance()->receiveData();
            
            ClientCore::Instance()->updateState();
            
            ClientCore::Instance()->renderWorld();
        }
        else if (ClientCore::Instance()->process() == 9) {
            ClientCore::Instance()->set_process(10);
            break;
        }
    }
    
    
    // Post-Game while
    while(Engine::main->isRunning()) {
        if(Engine::main->shouldUpdate()) {
            if (Engine::main->input->wasKeyReleased(KEY_ESCAPE)) {
                exit(1);
            }
            if (ClientCore::Instance()->process() == 10) {
                ClientCore::Instance()->resetGame();
            }
            ClientCore::Instance()->renderWorld();
        }
    }
    
    return 0;
}
