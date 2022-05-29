//
//  offline-main.cpp
//
//  Created by Kangming Yu on 5/15/22.
//

#include <signal.h>

#include "Core/OfflineCore/OfflineCore.hpp"
#include "KGLEngine/Engine.hpp"


int main(int argc, char* argv[]) {
    if (signal(SIGINT, destructOfflineCore) == SIG_ERR) {
        perror("Signal_handler error");
        exit(1);
    }

    int process = 1;
    int loadState = 1;

    OfflineCore::Instance()->initEngine(&process,&loadState);


    while(Engine::main->isRunning()) {

        if(Engine::main->shouldUpdate()) {

            if (process == 1) {
                
                // Logo =======================

                OfflineCore::Instance()->loadFont();

                OfflineCore::Instance()->displayLogo();

                process = 0;
            }
            else if (process == 2) {

                // Loading display =======================

                OfflineCore::Instance()->updateLoad();
            }
            else if (process == 3) {

                // Loading =========================

                if (loadState == 1) {
                    OfflineCore::Instance()->loadSky();
                }
                else if (loadState == 2) {
                    OfflineCore::Instance()->loadLight();
                }
                else if (loadState == 3) {
                    OfflineCore::Instance()->loadMap();
                }
                else if (loadState == 4) {
                    OfflineCore::Instance()->loadCharacter();
                }
                else if (loadState == 5) {
                    OfflineCore::Instance()->loadEnemy();
                }
                else if (loadState == 6) {
                    OfflineCore::Instance()->loadMagic();
                }
                else if (loadState == 7) {
                    OfflineCore::Instance()->loadAlly();
                }
                else if (loadState == 8) {
                    OfflineCore::Instance()->loadHUD();
                }
                else if (loadState == 9) {
                    OfflineCore::Instance()->loadDamageSystem();
                }
                else if (loadState == 10) {
                    OfflineCore::Instance()->loadStartScene();
                }
                else {
                    process = 4;
                }
            }
            else if (process == 4) {

                // Start Scnene===========================
                OfflineCore::Instance()->displayStart();

            }
            else if (process == 5) {
                OfflineCore::Instance()->updateStart();

                OfflineCore::Instance()->renderWorld();
            }
            else if (process == 6) {

                OfflineCore::Instance()->cameraHandle();

                //OfflineCore::Instance()->handleEvent();

                OfflineCore::Instance()->updateState();

            }

            /*OfflineCore::Instance()->handleEvent();*/

            OfflineCore::Instance()->render();

        }
    }
    
    return 0;
}
