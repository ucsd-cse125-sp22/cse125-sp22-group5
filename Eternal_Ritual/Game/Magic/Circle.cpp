//
//  Circle.cpp
//  Eternal_Ritual_Offline
//
//  Created by Zifan Zhang on 5/29/22.
//

#include "Circle.hpp"

using namespace glm;

Node* Circle::metaCircle = NULL;
bool Circle::loaded = NULL;
Texture* Circle::circleTexture = NULL;

void Circle::load() {
    this->loaded = true;
    circleTexture = new Texture("/Resources/Game/Effects/circle.png", 2.0f, true);
    this->metaCircle = new Node();
    metaCircle->loadModelFile("/Resources/Game/Effects/Sheet3.dae");
    metaCircle->geometries[0]->setDoubleSided();
    metaCircle->geometries[0]->renderingOrder = 1000;
}
Circle::Circle() {
    if (!loaded) load();
    shader = new PBRShader(0.2, 0.2);
    shader->setAdditive();
    shader->setDiffuseMap(circleTexture);
    this->circle = metaCircle->copy();
    this->circle->geometries[0]->setShader(shader);
    this->circle->geometries[0]->renderingBitMask = 1;
    this->addChildNode(this->circle);
}
void Circle::setColor(glm::vec3 color) {
    shader->multiplyColor = color;
    this->color = color;
}
Circle* Circle::copy() {
    Circle* newCircle = new Circle();
    newCircle->circle = this->circle->copy();
    newCircle->shader = this->shader->copy();
    newCircle->circle->geometries[0]->setShader(newCircle->shader);
    newCircle->setColor(this->color);
    return newCircle;
}
