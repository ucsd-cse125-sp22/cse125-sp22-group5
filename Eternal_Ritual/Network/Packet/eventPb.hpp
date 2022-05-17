#ifndef EVENTPB_HPP
#define EVENTPB_HPP

#include "common.hpp"
#include "pbData.hpp"
#include "../KGLEngine/Toolkit/libraries.h"


class EventPb : public PbData {
public:
    EventPb();
    ~EventPb();
    void readData(char* pbArr, int dataLen);
    char* sendData();
    void clearData();
    
    void setStart(bool start);
    bool getStart();
    
    void setRestart(bool restart);
    bool getRestart();
    
    void setPlayerName(string playerName);
    string getPlayerName();
    
    void addMagicEvent(gameDataPb::MagicPb magicEvent);
    bool hasMagicEvents();
    vector<gameDataPb::MagicPb> getMagicEvents();
    
    void addAddMagic(gameDataPb::MagicPb magicEvent);
    bool hasAddMagics();
    vector<gameDataPb::MagicPb> getAddMagics();
    
    void addRmMagic(gameDataPb::MagicPb magicEvent);
    bool hasRmMagics();
    vector<gameDataPb::MagicPb> getRmMagics();
    
    
    
    void setMouseTranslation(vec2 mouseTranslation);
    vec2 getMouseTranslation();
    
    void setControlNodeEulerAngles(vec3 controlNodeEulerAngles);
    vec3 getControlNodeEulerAngles();
    
    
    void addMovEvent(gameDataPb::MovEvent movEvent);
    queue<gameDataPb::MovEvent> getMovEvents();
    
    
    
private:
    gameDataPb::Event* eventData;
    char pbArr[99];
};

#endif /* eventPb_hpp */
