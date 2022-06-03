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
    
    OfflineCore::Instance()->initEngine();

    OfflineCore::Instance()->loadFont();

    OfflineCore::Instance()->loadSky();
    
    OfflineCore::Instance()->loadLight();
    
    OfflineCore::Instance()->loadMap();
    
    OfflineCore::Instance()->loadCharacter();
    
    OfflineCore::Instance()->loadEnemy();
    
    OfflineCore::Instance()->loadMagic();

    // =============================
    OfflineCore::Instance()->loadAlly();

    OfflineCore::Instance()->loadHUD();
    // =============================
    
    OfflineCore::Instance()->loadDamageSystem();
    
    while(Engine::main->isRunning()) {
        if(Engine::main->shouldUpdate()) {
            OfflineCore::Instance()->handleEvent();
            
            OfflineCore::Instance()->updateState();
            
            OfflineCore::Instance()->renderWorld();
        }
    }
    
    return 0;
}
