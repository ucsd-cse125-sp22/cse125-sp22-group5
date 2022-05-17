#include "statePb.hpp"

#include "clientCore.hpp"

using namespace gameDataPb;

StatePb::StatePb() {
    this->stateData = new State();
}

StatePb::~StatePb() {
    delete this->stateData;
}

void StatePb::readData(char* pbArr, int dataLen) {
    this->stateData->ParseFromArray(pbArr, dataLen);
//    if (!pbData.ParseFromArray(pbArr, dataLen)) {
//        perror("Parse protobuf data error");
//        exit(1);
//    }
}

char* StatePb::sendData() {
    this->dataLen = static_cast<int>(this->stateData->ByteSizeLong());

    std::cout << std::endl << this->stateData->DebugString() << std::endl;
    this->stateData->SerializeToArray(pbArr, MAX_PB_BUFFER_SIZE);
    
    return pbArr;
}

void StatePb::clearData() {
    this->stateData->Clear();
}



void StatePb::setPlayerIP(ulong playerIP) {
    this->stateData->set_playerip(playerIP);
}

ulong StatePb::getPlayerIP() {
    return this->stateData->playerip();
}


void StatePb::setPlayerName(ulong playerIP, string playerName) {
    if (!this->stateData->playerinfos().count(playerIP)) {
        State_PlayerInfo playerInfo;
        this->stateData->mutable_playerinfos()->insert({playerIP, playerInfo});
    }
    this->stateData->mutable_playerinfos()->at(playerIP).set_playername(playerName);
}

string StatePb::getPlayerName(ulong playerIP) {
    return this->stateData->playerinfos().at(playerIP).playername();
}


void StatePb::setDirState(ulong playerIP, DirState dirState) {
    if (!this->stateData->playerinfos().count(playerIP)) {
        State_PlayerInfo playerInfo;
        this->stateData->mutable_playerinfos()->insert({playerIP, playerInfo});
    }
    this->stateData->mutable_playerinfos()->at(playerIP).set_dirstate(dirState);
}

DirState StatePb::getDirState(ulong playerIP) {
    return this->stateData->playerinfos().at(playerIP).dirstate();
}


void StatePb::setPosition(ulong playerIP, vec3 position) {
    if (!this->stateData->playerinfos().count(playerIP)) {
        State_PlayerInfo playerInfo;
        this->stateData->mutable_playerinfos()->insert({playerIP, playerInfo});
    }
    this->stateData->mutable_playerinfos()->at(playerIP).mutable_position()->set_x(position.x);
    this->stateData->mutable_playerinfos()->at(playerIP).mutable_position()->set_y(position.y);
    this->stateData->mutable_playerinfos()->at(playerIP).mutable_position()->set_z(position.z);
}

vec3 StatePb::getPosition(ulong playerIP) {
    vec3 tempVec3;
    tempVec3.x = this->stateData->playerinfos().at(playerIP).position().x();
    tempVec3.y = this->stateData->playerinfos().at(playerIP).position().y();
    tempVec3.z = this->stateData->playerinfos().at(playerIP).position().z();
    return tempVec3;
}


void StatePb::setEulerAngle(ulong playerIP, vec3 eulerAngle) {
    if (!this->stateData->playerinfos().count(playerIP)) {
        State_PlayerInfo playerInfo;
        this->stateData->mutable_playerinfos()->insert({playerIP, playerInfo});
    }
    this->stateData->mutable_playerinfos()->at(playerIP).mutable_eulerangle()->set_x(eulerAngle.x);
    this->stateData->mutable_playerinfos()->at(playerIP).mutable_eulerangle()->set_y(eulerAngle.y);
    this->stateData->mutable_playerinfos()->at(playerIP).mutable_eulerangle()->set_z(eulerAngle.z);
}

vec3 StatePb::getEulerAngle(ulong playerIP) {
    vec3 tempVec3;
    tempVec3.x = this->stateData->playerinfos().at(playerIP).eulerangle().x();
    tempVec3.y = this->stateData->playerinfos().at(playerIP).eulerangle().y();
    tempVec3.z = this->stateData->playerinfos().at(playerIP).eulerangle().z();
    return tempVec3;
}


void StatePb::addMagicEvent(ulong playerIP, MagicPb magicEvent) {
    if (!this->stateData->playerinfos().count(playerIP)) {
        State_PlayerInfo playerInfo;
        this->stateData->mutable_playerinfos()->insert({playerIP, playerInfo});
    }
    this->stateData->mutable_playerinfos()->at(playerIP).add_magicevents(magicEvent);
}

bool StatePb::hasMagicEvents(ulong playerIP) {
    return this->stateData->mutable_playerinfos()->at(playerIP).magicevents_size();
}

vector<MagicPb> StatePb::getMagicEvents(ulong playerIP) {
    vector<MagicPb> magicEvents;
    for (int i = 0; i <  this->stateData->mutable_playerinfos()->at(playerIP).magicevents_size(); i++) {
        magicEvents.emplace_back(this->stateData->mutable_playerinfos()->at(playerIP).magicevents(i));
    }
    return magicEvents;
}


void StatePb::addAddMagic(ulong playerIP, MagicPb magicEvent) {
    if (!this->stateData->playerinfos().count(playerIP)) {
        State_PlayerInfo playerInfo;
        this->stateData->mutable_playerinfos()->insert({playerIP, playerInfo});
    }
    this->stateData->mutable_playerinfos()->at(playerIP).add_addmagics(magicEvent);
}

bool StatePb::hasAddMagics(ulong playerIP) {
    return this->stateData->mutable_playerinfos()->at(playerIP).addmagics_size();
}

vector<MagicPb> StatePb::getAddMagics(ulong playerIP) {
    vector<MagicPb> addMagics;
    for (int i = 0; i < this->stateData->mutable_playerinfos()->at(playerIP).addmagics_size(); i++) {
        addMagics.emplace_back(this->stateData->mutable_playerinfos()->at(playerIP).addmagics(i));
    }
    return addMagics;
}


void StatePb::addRmMagic(ulong playerIP, MagicPb magicEvent) {
    if (!this->stateData->playerinfos().count(playerIP)) {
        State_PlayerInfo playerInfo;
        this->stateData->mutable_playerinfos()->insert({playerIP, playerInfo});
    }
    this->stateData->mutable_playerinfos()->at(playerIP).add_rmmagics(magicEvent);
}

bool StatePb::hasRmMagics(ulong playerIP) {
    return this->stateData->mutable_playerinfos()->at(playerIP).rmmagics_size();
}

vector<MagicPb> StatePb::getRmMagics(ulong playerIP) {
    vector<MagicPb> rmMagics;
    for (int i = 0; i < this->stateData->mutable_playerinfos()->at(playerIP).rmmagics_size(); i++) {
        rmMagics.emplace_back(this->stateData->mutable_playerinfos()->at(playerIP).rmmagics(i));
    }
    return rmMagics;
}


vector<ulong> StatePb::getEnemyIPs(ulong playerIP) {
    vector<ulong> enemyIPs;
    for (auto& it : this->stateData->playerinfos()) {
        if (it.first != playerIP) {
            enemyIPs.emplace_back(it.first);
        }
    }
    return enemyIPs;
}

