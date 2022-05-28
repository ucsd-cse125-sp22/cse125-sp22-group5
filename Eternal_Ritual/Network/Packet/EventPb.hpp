//
//  EventPb.hpp
//
//  Created by Kangming Yu on 4/15/22.
//

#ifndef EVENTPB_HPP
#define EVENTPB_HPP

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Network/Packet/PbData.hpp"


class EventPb final : public PbData {
public:
    EventPb();
    ~EventPb();
    void readData(char* pbArr, int dataLen) override;
    char* sendData() override;
    void clearData() override;
    
    void setStart(bool start);
    bool getStart();
    
    void setRestart(bool restart);
    bool getRestart();
    
    void setPlayerName(std::string playerName);
    std::string getPlayerName();
    
    void setPlayerStyle(int playerStyle);
    int getPlayerStyle();
    
    void setPlayerGroup(int playerGroup);
    int getPlayerGroup();
    
    void setControlNodeEulerAngles(glm::vec3 controlNodeEulerAngles);
    glm::vec3 getControlNodeEulerAngles();
    
    void setMoveDirection(glm::vec3 moveDirection);
    glm::vec3 getMoveDirection();
    
    void setDirState(gameDataPb::DirState dirState);
    gameDataPb::DirState getDirState();
    
    void setCharStatePb(gameDataPb::CharStatePb charStatePb);
    gameDataPb::CharStatePb getCharStatePb();
    
    void setRoll(bool roll);
    bool getRoll();
    
    void setToggleLock(bool toggleLock);
    bool getToggleLock();
    
    void addMagicEvent(gameDataPb::MagicPb magicEvent);
    bool hasMagicEvents();
    std::vector<gameDataPb::MagicPb> getMagicEvents();
    
    void setPlayerHP(unsigned long playerIP, int playerHP);
    int getPlayerHP(unsigned long playerIP);
    
    void setPlayerMP(unsigned long playerIP, int playerMP);
    int getPlayerMP(unsigned long playerIP);
    
private:
    gameDataPb::Event* event_data_;
};

#endif /* EventPb_hpp */
