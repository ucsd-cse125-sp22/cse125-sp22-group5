//
//  StatePb.hpp
//
//  Created by Kangming Yu on 4/15/22.
//

#ifndef STATEPB_HPP
#define STATEPB_HPP

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Network/Packet/PbData.hpp"


class StatePb final : public PbData {
public:
    StatePb();
    ~StatePb();
    void readData(char* pbArr, int dataLen) override;
    char* sendData() override;
    void clearData() override;
    
    
    void setPlayerIP(unsigned long playerIP);
    unsigned long getPlayerIP();
    
    void setPlayerName(unsigned long playerIP, std::string playerName);
    std::string getPlayerName(unsigned long playerIP);
    
    void setPlayerStyle(unsigned long playerIP, int playerStyle);
    int getPlayerStyle(unsigned long playerIP);
    
    void setPlayerGroup(unsigned long playerIP, int playerGroup);
    int getPlayerGroup(unsigned long playerIP);
    
    void setControlNodeEulerAngles(unsigned long playerIP, glm::vec3 controlNodeEulerAngles);
    glm::vec3 getControlNodeEulerAngles(unsigned long playerIP);
    
    void setMoveDirection(unsigned long playerIP, glm::vec3 moveDirection);
    glm::vec3 getMoveDirection(unsigned long playerIP);
    
    void setDirState(unsigned long playerIP, gameDataPb::DirState dirState);
    gameDataPb::DirState getDirState(unsigned long playerIP);
    
    void setCharStatePb(unsigned long playerIP, gameDataPb::CharStatePb charStatePb);
    gameDataPb::CharStatePb getCharStatePb(unsigned long playerIP);
    
    void setRoll(unsigned long playerIP, bool roll);
    bool getRoll(unsigned long playerIP);
    
    void setToggleLock(unsigned long playerIP, bool toggleLock);
    bool getToggleLock(unsigned long playerIP);
    
    void addMagicEvent(unsigned long playerIP, gameDataPb::MagicPb magicEvent);
    bool hasMagicEvents(unsigned long playerIP);
    std::vector<gameDataPb::MagicPb> getMagicEvents(unsigned long playerIP);
    
    void setPlayerHP(unsigned long playerIP, int playerHP);
    int getPlayerHP(unsigned long playerIP);
    
    void setPlayerMP(unsigned long playerIP, int playerMP);
    int getPlayerMP(unsigned long playerIP);
    
    std::vector<unsigned long> getEnemyIPs(unsigned long playerIP);
    
private:
    gameDataPb::State* state_data_;
};


#endif /* StatePb_hpp */
