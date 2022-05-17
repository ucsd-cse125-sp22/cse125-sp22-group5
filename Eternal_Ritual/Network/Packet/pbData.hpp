#ifndef PBDATA_HPP
#define PBDATA_HPP

#include "common.hpp"
#include "gameData.pb.h"

#define MAX_PB_BUFFER_SIZE 1000


class PbData {
public:
    virtual ~PbData() {};
    virtual void readData(char* pbArr, int len) = 0;
    virtual char* sendData() = 0;
    virtual void clearData() = 0;
    unsigned long getPlayerIP();
    int getDataLen();

protected:
    unsigned long playerIP;
    int dataLen;
    
    char pbArr[MAX_PB_BUFFER_SIZE];
};

#endif /* pbData.hpp */
