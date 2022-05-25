//
//  server-main.cpp
//
//  Created by Kangming Yu on 4/15/22.
//

#include <signal.h>

#include "Core/ServerCore/ServerCore.hpp"


int main(int argc, char* argv[]) {
    if (signal(SIGINT, destructClientCore) == SIG_ERR) {
        perror("Signal_handler error");
        exit(1);
    }
    
    ServerCore::Instance()->openServer();
    
    ServerCore::Instance()->initPbPacket();
    
    while (true) {
        ServerCore::Instance()->setTickEnd();
        
        ServerCore::Instance()->receiveData();
    
        ServerCore::Instance()->updateState();

        ServerCore::Instance()->sendData();
        
        ServerCore::Instance()->waitTickEnd();
    }
    
    return 0;
}
