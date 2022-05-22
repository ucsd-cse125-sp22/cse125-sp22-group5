#include "Network/ClientSide/common.hpp"
#include "Core/ClientCore/clientCore.hpp"


ClientCore* ClientCore::clientCore = nullptr;


int no_main(int argc, char* argv[]) {
    if (signal(SIGINT, signal_handler_fun) == SIG_ERR) {
        perror("Signal_handler error");
        exit(1);
    }
    
    ClientCore::Instance()->initEngine();

    ClientCore::Instance()->loadSky();
    
    ClientCore::Instance()->loadLight();
    
    ClientCore::Instance()->loadScene();
    
    ClientCore::Instance()->loadCharacter();
    
    ClientCore::Instance()->loadWeapon();
    
    
    ClientCore::Instance()->initPbPacket();
    
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
