#include "eventPb.hpp"
#include "clientCore.hpp"


using namespace gameDataPb;


EventPb::EventPb() {
    this->eventData = new Event();
}

EventPb::~EventPb() {
    delete this->eventData;
}

void EventPb::readData(char* pbArr, int dataLen) {    
    this->eventData->ParseFromArray(pbArr, dataLen);
//    if (!pbData.ParseFromArray(pbArr, dataLen)) {
//        perror("Parse protobuf data error");
//        exit(1);
//    }
}

char* EventPb::sendData() {
    this->dataLen = static_cast<int>(this->eventData->ByteSizeLong());

    std::cout << "DataLen (in eventPb): " << this->dataLen << std::endl;
    std::cout << std::endl << this->eventData->DebugString() << std::endl;
    
    this->eventData->SerializeToArray(pbArr, MAX_PB_BUFFER_SIZE);

    return pbArr;
}

void EventPb::clearData() {
    this->eventData->Clear();
}




void EventPb::setStart(bool start) {
    this->eventData->set_start(start);
}

bool EventPb::getStart() {
    return this->eventData->start();
}


void EventPb::setRestart(bool restart) {
    this->eventData->set_restart(restart);
}

bool EventPb::getRestart() {
    return this->eventData->restart();
}


void EventPb::setPlayerName(string playerName) {
    this->eventData->set_playername(playerName);
}

string EventPb::getPlayerName() {
    return this->eventData->playername();
}


void EventPb::addMagicEvent(MagicPb magicEvent) {
    this->eventData->add_magicevents(magicEvent);
}

bool EventPb::hasMagicEvents() {
    return this->eventData->magicevents_size();
}

vector<MagicPb> EventPb::getMagicEvents() {
    vector<MagicPb> magicEvents;
    for (int i = 0; i < this->eventData->magicevents_size(); i++) {
        magicEvents.emplace_back(this->eventData->magicevents(i));
    }
    return magicEvents;
}


void EventPb::addAddMagic(MagicPb magicEvent) {
    this->eventData->add_addmagics(magicEvent);
}

bool EventPb::hasAddMagics() {
    return this->eventData->addmagics_size();
}

vector<MagicPb> EventPb::getAddMagics() {
    vector<MagicPb> addMagics;
    for (int i = 0; i < this->eventData->addmagics_size(); i++) {
        addMagics.emplace_back(this->eventData->addmagics(i));
    }
    return addMagics;
}


void EventPb::addRmMagic(MagicPb magicEvent) {
    this->eventData->add_rmmagics(magicEvent);
}

bool EventPb::hasRmMagics() {
    return this->eventData->rmmagics_size();
}

vector<MagicPb> EventPb::getRmMagics() {
    vector<MagicPb> rmMagics;
    for (int i = 0; i < this->eventData->rmmagics_size(); i++) {
        rmMagics.emplace_back(this->eventData->rmmagics(i));
    }
    return rmMagics;
}


void EventPb::setMouseTranslation(vec2 mouseTranslation) {
    this->eventData->mutable_mousetranslation()->set_x(mouseTranslation.x);
    this->eventData->mutable_mousetranslation()->set_y(mouseTranslation.y);
}

vec2 EventPb::getMouseTranslation() {
    vec2 tempVec2;
    tempVec2.x = this->eventData->mousetranslation().x();
    tempVec2.y = this->eventData->mousetranslation().y();
    return tempVec2;
}


void EventPb::setControlNodeEulerAngles(vec3 controlNodeEulerAngles) {
    this->eventData->mutable_controlnodeeulerangles()->set_x(controlNodeEulerAngles.x);
    this->eventData->mutable_controlnodeeulerangles()->set_y(controlNodeEulerAngles.y);
    this->eventData->mutable_controlnodeeulerangles()->set_z(controlNodeEulerAngles.z);
}

vec3 EventPb::getControlNodeEulerAngles() {
    vec3 tempVec3;
    tempVec3.x = this->eventData->controlnodeeulerangles().x();
    tempVec3.y = this->eventData->controlnodeeulerangles().y();
    tempVec3.z = this->eventData->controlnodeeulerangles().z();
    return tempVec3;
}


void EventPb::addMovEvent(MovEvent movEvent) {
    this->eventData->add_movevents(movEvent);
}

queue<MovEvent> EventPb::getMovEvents() {
    queue<MovEvent> movEvents;
    for (int i = 0; i < this->eventData->movevents_size(); i++) {
        movEvents.emplace(this->eventData->movevents(i));
    }
    return movEvents;
}
