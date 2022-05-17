#ifndef STATEPB_HPP
#define STATEPB_HPP

#include "common.hpp"
#include "pbData.hpp"
#include "../KGLEngine/Toolkit/libraries.h"



class StatePb : public PbData {
public:
    StatePb();
    ~StatePb();
    void readData(char* pbArr, int dataLen);
    char* sendData();
    void clearData();
    
    
    void setPlayerIP(unsigned long playerIP);
    unsigned long getPlayerIP();
    
    void setPlayerName(unsigned long playerIP, string playerName);
    string getPlayerName(unsigned long playerIP);
    
    void setDirState(unsigned long playerIP, gameDataPb::DirState dirState);
    gameDataPb::DirState getDirState(unsigned long playerIP);
    
    void setPosition(unsigned long playerIP, vec3 position);
    vec3 getPosition(unsigned long playerIP);
    
    void setEulerAngle(unsigned long playerIP, vec3 eulerAngle);
    vec3 getEulerAngle(unsigned long playerIP);
    
    void addMagicEvent(unsigned long playerIP, gameDataPb::MagicPb magicEvent);
    bool hasMagicEvents(unsigned long playerIP);
    vector<gameDataPb::MagicPb> getMagicEvents(unsigned long playerIP);
    
    void addAddMagic(unsigned long playerIP, gameDataPb::MagicPb magicEvent);
    bool hasAddMagics(unsigned long playerIP);
    vector<gameDataPb::MagicPb> getAddMagics(unsigned long playerIP);
    
    void addRmMagic(unsigned long playerIP, gameDataPb::MagicPb magicEvent);
    bool hasRmMagics(unsigned long playerIP);
    vector<gameDataPb::MagicPb> getRmMagics(unsigned long playerIP);
    
    vector<unsigned long> getEnemyIPs(unsigned long playerIP);

    
private:

    gameDataPb::State* stateData;
};


#endif /* statePb_hpp */
