//
//  client-main.cpp
//
//  Created by Kangming Yu on 4/15/22.
//

#include <signal.h>
#include <iostream>


#include "Core/ClientCore/ClientCore.hpp"



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

    ClientCore::Instance()->loadSky();
    
    ClientCore::Instance()->loadLight();
    
    ClientCore::Instance()->loadScene();
    
    ClientCore::Instance()->loadCharacter();
    
    ClientCore::Instance()->loadMagic();
    
    ClientCore::Instance()->loadFont();
    
    ClientCore::Instance()->loadDamageSystem();
    
    
    ClientCore::Instance()->loadPbPacket();
    
    ClientCore::Instance()->connectServer();
    

    
    while (true) {
        gettimeofday(timepre, NULL);
        ClientCore::Instance()->handleEvent();
        gettimeofday(timecurr, NULL);
        std::cout << "handleEvent" << std::endl;
        printtime(timecurr, timepre);
        
        gettimeofday(timepre, NULL);
        ClientCore::Instance()->sendData();
        gettimeofday(timecurr, NULL);
        std::cout << "sendData" << std::endl;
        printtime(timecurr, timepre);

        gettimeofday(timepre, NULL);
        ClientCore::Instance()->receiveData();
        gettimeofday(timecurr, NULL);
        std::cout << "receiveData" << std::endl;
        printtime(timecurr, timepre);
        
        gettimeofday(timepre, NULL);
        ClientCore::Instance()->updateState();
        gettimeofday(timecurr, NULL);
        std::cout << "updateState" << std::endl;
        printtime(timecurr, timepre);
        
        gettimeofday(timepre, NULL);
        ClientCore::Instance()->renderWorld();
        gettimeofday(timecurr, NULL);
        std::cout << "renderWorld" << std::endl;
        printtime(timecurr, timepre);
    }
    
    return 0;
}
