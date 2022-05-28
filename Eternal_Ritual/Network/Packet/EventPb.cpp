//
//  EventPb.cpp
//
//  Created by Kangming Yu on 4/15/22.
//

#include "Network/Packet/EventPb.hpp"

using namespace gameDataPb;
using namespace glm;
using namespace std;


EventPb::EventPb() {
    event_data_ = new Event();
}

EventPb::~EventPb() {
    delete event_data_;
}

void EventPb::readData(char* pbArr, int dataLen) {    
    event_data_->ParseFromArray(pbArr, dataLen);
}

char* EventPb::sendData() {
    data_len_ = static_cast<int>(event_data_->ByteSizeLong());

    std::cout << "DataLen (in eventPb): " << data_len_ << std::endl;
    std::cout << std::endl << event_data_->DebugString() << std::endl;
    
    event_data_->SerializeToArray(pb_arr_, MAX_PB_BUFFER_SIZE);
    
    event_data_->ParseFromArray(pb_arr_, data_len_);

    return pb_arr_;
}

void EventPb::clearData() {
    event_data_->Clear();
}


void EventPb::setStart(bool start) {
    event_data_->set_start(start);
}

bool EventPb::getStart() {
    return event_data_->start();
}


void EventPb::setRestart(bool restart) {
    event_data_->set_restart(restart);
}

bool EventPb::getRestart() {
    return event_data_->restart();
}


void EventPb::setPlayerName(string playerName) {
    event_data_->set_playername(playerName);
}

string EventPb::getPlayerName() {
    return event_data_->playername();
}


void EventPb::setPlayerStyle(int playerStyle) {
    event_data_->set_playerstyle(playerStyle);
}

int EventPb::getPlayerStyle() {
    return event_data_->playerstyle();
}


void EventPb::setPlayerGroup(int playerGroup) {
    event_data_->set_playergroup(playerGroup);
}

int EventPb::getPlayerGroup() {
    return event_data_->playergroup();
}


void EventPb::setControlNodeEulerAngles(vec3 controlNodeEulerAngles) {
    event_data_->mutable_controlnodeeulerangles()->set_x(controlNodeEulerAngles.x);
    event_data_->mutable_controlnodeeulerangles()->set_y(controlNodeEulerAngles.y);
    event_data_->mutable_controlnodeeulerangles()->set_z(controlNodeEulerAngles.z);
}

vec3 EventPb::getControlNodeEulerAngles() {
    vec3 tempVec3;
    tempVec3.x = event_data_->controlnodeeulerangles().x();
    tempVec3.y = event_data_->controlnodeeulerangles().y();
    tempVec3.z = event_data_->controlnodeeulerangles().z();
    return tempVec3;
}


void EventPb::setMoveDirection(vec3 moveDirection) {
    event_data_->mutable_movedirection()->set_x(moveDirection.x);
    event_data_->mutable_movedirection()->set_y(moveDirection.y);
    event_data_->mutable_movedirection()->set_z(moveDirection.z);
}

vec3 EventPb::getMoveDirection() {
    vec3 tempVec3;
    tempVec3.x = event_data_->movedirection().x();
    tempVec3.y = event_data_->movedirection().y();
    tempVec3.z = event_data_->movedirection().z();
    return tempVec3;
}


void EventPb::setDirState(DirState dirState) {
    event_data_->set_dirstate(dirState);
}

DirState EventPb::getDirState() {
    return event_data_->dirstate();
}


void EventPb::setCharStatePb(gameDataPb::CharStatePb charStatePb) {
    event_data_->set_charstatepb(charStatePb);
}

gameDataPb::CharStatePb EventPb::getCharStatePb() {
    return event_data_->charstatepb();
}


void EventPb::setRoll(bool roll) {
    event_data_->set_roll(roll);
}

bool EventPb::getRoll() {
    return event_data_->roll();
}


void EventPb::setToggleLock(bool toggleLock) {
    event_data_->set_togglelock(toggleLock);
}

bool EventPb::getToggleLock() {
    return event_data_->togglelock();
}


void EventPb::addMagicEvent(MagicPb magicEvent) {
    event_data_->add_magicevents(magicEvent);
}

bool EventPb::hasMagicEvents() {
    return event_data_->magicevents_size();
}

vector<MagicPb> EventPb::getMagicEvents() {
    vector<MagicPb> magicEvents;
    for (int i = 0; i < event_data_->magicevents_size(); i++) {
        magicEvents.emplace_back(event_data_->magicevents(i));
    }
    return magicEvents;
}


void EventPb::setPlayerHP(unsigned long playerIP, int playerHP) {
    if (!event_data_->playerattrs().count(playerIP)) {
        PlayerAttr playerAttr;
        event_data_->mutable_playerattrs()->insert({playerIP, playerAttr});
    }
    event_data_->mutable_playerattrs()->at(playerIP).set_playerhp(playerHP);
}

int EventPb::getPlayerHP(unsigned long playerIP){
    return event_data_->playerattrs().at(playerIP).playerhp();
}


void EventPb::setPlayerMP(unsigned long playerIP, int playerMP) {
    if (!event_data_->playerattrs().count(playerIP)) {
        PlayerAttr playerAttr;
        event_data_->mutable_playerattrs()->insert({playerIP, playerAttr});
    }
    event_data_->mutable_playerattrs()->at(playerIP).set_playermp(playerMP);
}

int EventPb::getPlayerMP(unsigned long playerIP){
    return event_data_->playerattrs().at(playerIP).playermp();
}

