#include "common.hpp"
#include "serverCore.hpp"


ServerCore* ServerCore::serverCore = nullptr;

void signal_handler_func(int signum) {
    std::cout << "Game over" << std::endl;
    
    ServerCore::Instance()->closeServer();
    
    ServerCore::Destructor();
    
    exit(1);
}


int main(int argc, char* argv[]) {
    if (signal(SIGINT, signal_handler_func) == SIG_ERR) {
        perror("Signal_handler error");
        exit(1);
    }
    
    ServerCore::Instance()->openServer();
    
    ServerCore::Instance()->initPbPacket();
    
    ServerCore::Instance()->initEngine();
    
//    ServerCore::Instance()->loadScene();
    
    ServerCore::Instance()->loadCharacters();
    
    while (true) {
        ServerCore::Instance()->setTickEnd();
        
        ServerCore::Instance()->receiveData();
    
        ServerCore::Instance()->updateState();

        ServerCore::Instance()->sendData();
        
        ServerCore::Instance()->waitTickEnd();
    }
    
    return 0;
}
