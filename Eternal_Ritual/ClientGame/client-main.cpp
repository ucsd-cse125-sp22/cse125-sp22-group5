//
//  client-main.cpp
//
//  Created by Kangming Yu on 4/15/22.
//

#include <signal.h>

#include "Core/ClientCore/ClientCore.hpp"


int main(int argc, char* argv[]) {
    if (signal(SIGINT, destructClientCore) == SIG_ERR) {
        perror("Signal_handler error");
        exit(1);
    }
    
    ClientCore::Instance()->initEngine();

    ClientCore::Instance()->loadSky();
    
    ClientCore::Instance()->loadLight();
    
    ClientCore::Instance()->loadScene();
    
    ClientCore::Instance()->loadCharacter();
    
    ClientCore::Instance()->loadMagic();
    
    ClientCore::Instance()->loadFont();
    
    ClientCore::Instance()->loadHUD();
    
    ClientCore::Instance()->loadDamageSystem();
    
    
    ClientCore::Instance()->loadPbPacket();
    
    ClientCore::Instance()->connectServer();
    
    while (true) {
        ClientCore::Instance()->handleEvent();
        
        ClientCore::Instance()->sendData();
        
        ClientCore::Instance()->receiveData();
        
        ClientCore::Instance()->updateState();
        
        ClientCore::Instance()->renderWorld();
    }
    
    return 0;
}
