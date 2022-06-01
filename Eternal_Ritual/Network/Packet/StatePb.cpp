//
//  StatePb.cpp
//
//  Created by Kangming Yu on 4/15/22.
//

#include "Network/Packet/StatePb.hpp"

using namespace gameDataPb;
using namespace glm;
using namespace std;


StatePb::StatePb() {
    state_data_ = new State();
}

StatePb::~StatePb() {
    delete state_data_;
}

void StatePb::readData(char* pbArr, int dataLen) {
    state_data_->ParseFromArray(pbArr, dataLen);
}

char* StatePb::sendData() {
    data_len_ = static_cast<int>(state_data_->ByteSizeLong());

    //std::cout << std::endl << state_data_->DebugString() << std::endl;
    state_data_->SerializeToArray(pb_arr_, MAX_PB_BUFFER_SIZE);
    
    return pb_arr_;
}

void StatePb::clearData() {
    state_data_->Clear();
}


void StatePb::setPlayerIP(unsigned long playerIP) {
    state_data_->set_playerip(playerIP);
}

unsigned long StatePb::getPlayerIP() {
    return state_data_->playerip();
}


void StatePb::setPlayerName(unsigned long playerIP, string playerName) {
    if (!state_data_->playerinfos().count(playerIP)) {
        State_PlayerInfo playerInfo;
        state_data_->mutable_playerinfos()->insert({playerIP, playerInfo});
    }
    state_data_->mutable_playerinfos()->at(playerIP).set_playername(playerName);
}

string StatePb::getPlayerName(unsigned long playerIP) {
    return state_data_->playerinfos().at(playerIP).playername();
}


void StatePb::setPlayerStyle(unsigned long playerIP, int playerStyle) {
    if (!state_data_->playerinfos().count(playerIP)) {
        State_PlayerInfo playerInfo;
        state_data_->mutable_playerinfos()->insert({playerIP, playerInfo});
    }
    state_data_->mutable_playerinfos()->at(playerIP).set_playerstyle(playerStyle);
}

int StatePb::getPlayerStyle(unsigned long playerIP) {
    return state_data_->playerinfos().at(playerIP).playerstyle();
}


void StatePb::setPlayerGroup(unsigned long playerIP, int playerGroup) {
    if (!state_data_->playerinfos().count(playerIP)) {
        State_PlayerInfo playerInfo;
        state_data_->mutable_playerinfos()->insert({playerIP, playerInfo});
    }
    state_data_->mutable_playerinfos()->at(playerIP).set_playergroup(playerGroup);
}

int StatePb::getPlayerGroup(unsigned long playerIP) {
    return state_data_->playerinfos().at(playerIP).playergroup();
}


void StatePb::setControlNodeEulerAngles(unsigned long playerIP, glm::vec3 controlNodeEulerAngles) {
    if (!state_data_->playerinfos().count(playerIP)) {
        State_PlayerInfo playerInfo;
        state_data_->mutable_playerinfos()->insert({playerIP, playerInfo});
    }
    state_data_->mutable_playerinfos()->at(playerIP).mutable_controlnodeeulerangles()->set_x(controlNodeEulerAngles.x);
    state_data_->mutable_playerinfos()->at(playerIP).mutable_controlnodeeulerangles()->set_y(controlNodeEulerAngles.y);
    state_data_->mutable_playerinfos()->at(playerIP).mutable_controlnodeeulerangles()->set_z(controlNodeEulerAngles.z);
}

vec3 StatePb::getControlNodeEulerAngles(unsigned long playerIP) {
    vec3 tempVec3;
    tempVec3.x = state_data_->playerinfos().at(playerIP).controlnodeeulerangles().x();
    tempVec3.y = state_data_->playerinfos().at(playerIP).controlnodeeulerangles().y();
    tempVec3.z = state_data_->playerinfos().at(playerIP).controlnodeeulerangles().z();
    return tempVec3;
}


void StatePb::setMoveDirection(unsigned long playerIP, glm::vec3 moveDirection) {
    if (!state_data_->playerinfos().count(playerIP)) {
        State_PlayerInfo playerInfo;
        state_data_->mutable_playerinfos()->insert({playerIP, playerInfo});
    }
    state_data_->mutable_playerinfos()->at(playerIP).mutable_movedirection()->set_x(moveDirection.x);
    state_data_->mutable_playerinfos()->at(playerIP).mutable_movedirection()->set_y(moveDirection.y);
    state_data_->mutable_playerinfos()->at(playerIP).mutable_movedirection()->set_z(moveDirection.z);
}

vec3 StatePb::getMoveDirection(unsigned long playerIP) {
    vec3 tempVec3;
    tempVec3.x = state_data_->playerinfos().at(playerIP).movedirection().x();
    tempVec3.y = state_data_->playerinfos().at(playerIP).movedirection().y();
    tempVec3.z = state_data_->playerinfos().at(playerIP).movedirection().z();
    return tempVec3;
}


void StatePb::setDirState(unsigned long playerIP, DirState dirState) {
    if (!state_data_->playerinfos().count(playerIP)) {
        State_PlayerInfo playerInfo;
        state_data_->mutable_playerinfos()->insert({playerIP, playerInfo});
    }
    state_data_->mutable_playerinfos()->at(playerIP).set_dirstate(dirState);
}

DirState StatePb::getDirState(unsigned long playerIP) {
    return state_data_->playerinfos().at(playerIP).dirstate();
}


void StatePb::setCharStatePb(unsigned long playerIP, gameDataPb::CharStatePb charStatePb) {
    if (!state_data_->playerinfos().count(playerIP)) {
        State_PlayerInfo playerInfo;
        state_data_->mutable_playerinfos()->insert({playerIP, playerInfo});
    }
    state_data_->mutable_playerinfos()->at(playerIP).set_charstatepb(charStatePb);
}

gameDataPb::CharStatePb StatePb::getCharStatePb(unsigned long playerIP) {
    return state_data_->playerinfos().at(playerIP).charstatepb();
}


void StatePb::setRoll(unsigned long playerIP, bool roll) {
    if (!state_data_->playerinfos().count(playerIP)) {
        State_PlayerInfo playerInfo;
        state_data_->mutable_playerinfos()->insert({playerIP, playerInfo});
    }
    state_data_->mutable_playerinfos()->at(playerIP).set_roll(roll);
}

bool StatePb::getRoll(unsigned long playerIP) {
    return state_data_->playerinfos().at(playerIP).roll();
}


void StatePb::setToggleLock(unsigned long playerIP, bool toggleLock) {
    if (!state_data_->playerinfos().count(playerIP)) {
        State_PlayerInfo playerInfo;
        state_data_->mutable_playerinfos()->insert({playerIP, playerInfo});
    }
    state_data_->mutable_playerinfos()->at(playerIP).set_togglelock(toggleLock);
}

bool StatePb::getToggleLock(unsigned long playerIP) {
    return state_data_->playerinfos().at(playerIP).togglelock();
}


void StatePb::addMagicEvent(unsigned long playerIP, MagicPb magicEvent) {
    if (!state_data_->playerinfos().count(playerIP)) {
        State_PlayerInfo playerInfo;
        state_data_->mutable_playerinfos()->insert({playerIP, playerInfo});
    }
    state_data_->mutable_playerinfos()->at(playerIP).add_magicevents(magicEvent);
}

bool StatePb::hasMagicEvents(unsigned long playerIP) {
    return state_data_->mutable_playerinfos()->at(playerIP).magicevents_size();
}

vector<MagicPb> StatePb::getMagicEvents(unsigned long playerIP) {
    vector<MagicPb> magicEvents;
    for (int i = 0; i <  state_data_->mutable_playerinfos()->at(playerIP).magicevents_size(); i++) {
        magicEvents.emplace_back(state_data_->mutable_playerinfos()->at(playerIP).magicevents(i));
    }
    return magicEvents;
}


void StatePb::setPlayerHP(unsigned long playerIP, int playerHP) {
    if (!state_data_->playerattrs().count(playerIP)) {
        PlayerAttr playerAttr;
        state_data_->mutable_playerattrs()->insert({playerIP, playerAttr});
    }
    state_data_->mutable_playerattrs()->at(playerIP).set_playerhp(playerHP);
}

int StatePb::getPlayerHP(unsigned long playerIP){
    return state_data_->playerattrs().at(playerIP).playerhp();
}


void StatePb::setPlayerMP(unsigned long playerIP, int playerMP) {
    if (!state_data_->playerattrs().count(playerIP)) {
        PlayerAttr playerAttr;
        state_data_->mutable_playerattrs()->insert({playerIP, playerAttr});
    }
    state_data_->mutable_playerattrs()->at(playerIP).set_playermp(playerMP);
}

int StatePb::getPlayerMP(unsigned long playerIP){
    return state_data_->playerattrs().at(playerIP).playermp();
}


vector<unsigned long> StatePb::getEnemyIPs(unsigned long playerIP) {
    vector<unsigned long> enemyIPs;
    for (auto& it : state_data_->playerinfos()) {
        if (it.first != playerIP) {
            enemyIPs.emplace_back(it.first);
//            cout << it.first << endl;
        }
    }
    return enemyIPs;
}
