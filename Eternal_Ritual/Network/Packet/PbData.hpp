//
//  PbData.hpp
//
//  Created by Kangming Yu on 4/15/22.
//

#ifndef PBDATA_HPP
#define PBDATA_HPP

#include "Network/Packet/gameData.pb.h"

#define MAX_PB_BUFFER_SIZE 1000


class PbData {
public:
    virtual ~PbData() {};
    virtual void readData(char* pbArr, int len) = 0;
    virtual char* sendData() = 0;
    virtual void clearData() = 0;
    unsigned long player_ip();
    int data_len();

protected:
    unsigned long player_ip_;
    int data_len_;
    
    char pb_arr_[MAX_PB_BUFFER_SIZE];
};

#endif /* PbData.hpp */
