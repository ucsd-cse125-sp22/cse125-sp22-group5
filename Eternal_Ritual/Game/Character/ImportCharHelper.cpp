//
//  ImportCharHelper.cpp
//
//  Created by Kangming Yu on 5/16/22.
//

#include "Game/Character/ImportCharHelper.hpp"

#include "KGLEngine/Engine.hpp"

using namespace glm;


namespace ImportCharHelper {

void importCharModel(CharNode* character) {
    Node* charModel = new Node();
    charModel->scale = vec3(0.5f);
    charModel->loadModelFile("/Resources/Game/Character/Character.dae");
    charModel->isDisabled = false;
    if(true) {
        PBRShader* shader = new PBRShader(0.2f, 0.8f);
        shader->setDiffuseMap(new Texture("/Resources/Game/Character/BootsD.png", 2.0f, true));
        shader->setNormalMap(new Texture("/Resources/Game/Character/BootsN.png", 1.0f, true));
        shader->setAmbientOcclusionMap(new Texture("/Resources/Game/Character/BootsAO.png", 1.0f, true));
        charModel->geometries[0]->setShader(shader);
        charModel->geometries[1]->setShader(shader);
        charModel->geometries[6]->setShader(shader);
    }
    if(true) {
        PBRShader* shader = new PBRShader(0.2f, 0.8f);
        shader->setDiffuseMap(new Texture("/Resources/Game/Character/GlovesD.png", 2.0f, true));
        shader->setNormalMap(new Texture("/Resources/Game/Character/GlovesN.png", 1.0f, true));
        shader->setAmbientOcclusionMap(new Texture("/Resources/Game/Character/GlovesAO.png", 1.0f, true));
        charModel->geometries[2]->setShader(shader);
        charModel->geometries[3]->setShader(shader);
        charModel->geometries[4]->setShader(shader);
        charModel->geometries[5]->setShader(shader);
    }
    if(true) {
        PBRShader* shader = new PBRShader("/Resources/Game/Character/Character", 0.1f, 0.9f);
        shader->setDiffuseMap(new Texture("/Resources/Game/Character/BodyD.png", 2.0f, true));
        //shader->setNormalMap(new Texture("/Resources/Game/Character/BodyN.png", 1.0f, true));
        //shader->setAmbientOcclusionMap(new Texture("/Resources/Game/Character/BodyAO.png", 1.0f, true));
        shader->setFloat("shadowBias", 0.05f);
        charModel->geometries[7]->setShader(shader);
        charModel->geometries[13]->setShader(shader);
    }
    if(true) {
        PBRShader* shader = new PBRShader("/Resources/Game/Character/Character", 0.4f, 0.4f);
        shader->setDiffuseMap(new Texture("/Resources/Game/Character/ChestD.png", 2.0f, true));
        shader->setNormalMap(new Texture("/Resources/Game/Character/ChestN.png", 1.0f, true));
        shader->setAmbientOcclusionMap(new Texture("/Resources/Game/Character/ChestAO.png", 1.0f, true));
        shader->setFloat("shadowBias", 0.01f);
        charModel->geometries[8]->setShader(shader);
        charModel->geometries[9]->setShader(shader);
        charModel->geometries[10]->setShader(shader);
        charModel->geometries[11]->setShader(shader);
        charModel->geometries[12]->setShader(shader);
    }
    if(true) {
        PBRShader* shader = new PBRShader(0.8f, 0.2f);
        shader->setDiffuseMap(new Texture("/Resources/Game/Character/StaffD.png", 2.0f, true));
        shader->setNormalMap(new Texture("/Resources/Game/Character/StaffN.png", 1.0f, true));
        shader->setAmbientOcclusionMap(new Texture("/Resources/Game/Character/StaffAO.png", 1.0f, true));
        charModel->geometries[14]->setShader(shader);
    }
    if(true) {
        PBRShader* shader = new PBRShader(0.8f, 0.2f);
        shader->setDiffuseMap(new Texture("/Resources/Game/Character/HelmetD.png", 2.0f, true));
        shader->setNormalMap(new Texture("/Resources/Game/Character/HelmetN.png", 1.0f, true));
        shader->setAmbientOcclusionMap(new Texture("/Resources/Game/Character/HelmetAO.png", 1.0f, true));
        charModel->geometries[15]->setShader(shader);
        charModel->geometries[16]->setShader(shader);
    }
    if(true) {
        PBRShader* shader = new PBRShader(0.2f, 0.2f);
        shader->setDiffuseMap(new Texture("/Resources/Game/Character/EyeD.png", 2.0f, true));
        charModel->geometries[17]->setShader(shader);
    }
    if(true) {
        PBRShader* shader = new PBRShader("/Resources/Game/Character/Character", 0.1f, 0.9f);
        shader->setDiffuseMap(new Texture("/Resources/Game/Character/HeadD.png", 2.0f, true));
        //shader->setNormalMap(new Texture("/Resources/Game/Character/HeadN.png", 1.0f, true));
        //shader->setAmbientOcclusionMap(new Texture("/Resources/Game/Character/HeadAO.png", 1.0f, true));
        shader->setFloat("shadowBias", 0.5f);
        charModel->geometries[18]->setShader(shader);
    }
    if(true) {
        PBRShader* shader = new PBRShader(0.5f, 0.5f);
        shader->setDiffuseMap(new Texture("/Resources/Game/Character/PantsD.png", 2.0f, true));
        shader->setNormalMap(new Texture("/Resources/Game/Character/PantsN.png", 1.0f, true));
        charModel->geometries[19]->setShader(shader);
    }
    if(true) {
        PBRShader* shader = new PBRShader(0.0f, 1.0f);
        shader->setDiffuseMap(new Texture("/Resources/Game/Character/HairD.png", 1.0f, true));
        charModel->geometries[20]->setShader(shader);
        charModel->geometries[20]->setDoubleSided();
        charModel->geometries[21]->setShader(shader);
        charModel->geometries[21]->setDoubleSided();
        charModel->geometries[22]->setShader(shader);
        charModel->geometries[22]->setDoubleSided();
        charModel->geometries[23]->setShader(shader);
        charModel->geometries[23]->setDoubleSided();
    }
    if(true) {
        PBRShader* shader = new PBRShader(0.0f, 1.0f);
        shader->setDiffuseMap(new Texture("/Resources/Game/Character/HairBaseD.png", 1.0f, true));
        charModel->geometries[24]->setShader(shader);
    }
    charModel->position = vec3(0.0f, 0.01f, 0.0f);
    charModel->eulerAngles = vec3(0.0f, 45.0f, 0.0f);
    charModel->scale = vec3(0.9f);
    
    character->setModel(charModel);
}


void importCharAnimation(CharNode* character) {
    Animator* idle = character->addAnimator("idle", "/Resources/Game/Character/Animations/Idle.dae");
    idle->play(0.2);
    idle->animatorBitMask = Bitmask::IDLE;
    Animator* running = character->addAnimator("running", "/Resources/Game/Character/Animations/Running.dae");
    running->animatorBitMask = Bitmask::RUNNING;
    Animator* fwdWalk = character->addAnimator("fwd walk", "/Resources/Game/Character/Animations/Walk Fwd.dae");
    fwdWalk->animatorBitMask = Bitmask::WALKFWD;
    Animator* backWalk = character->addAnimator("back walk", "/Resources/Game/Character/Animations/Walk Bck.dae");
    backWalk->animatorBitMask = Bitmask::WALKBCK;
    Animator* leftStrafe = character->addAnimator("left strafe", "/Resources/Game/Character/Animations/Left Strafe.dae");
    leftStrafe->animatorBitMask = Bitmask::WALKLEFT;
    Animator* rightStrafe = character->addAnimator("right strafe", "/Resources/Game/Character/Animations/Right Strafe.dae");
    rightStrafe->animatorBitMask = Bitmask::WALKRIGHT;
    Animator* frontRight = character->addAnimator("front right", "/Resources/Game/Character/Animations/Front Right.dae");
    frontRight->animatorBitMask = Bitmask::WALKFR;
    Animator* frontLeft = character->addAnimator("front left", "/Resources/Game/Character/Animations/Front Left.dae");
    frontLeft->animatorBitMask = Bitmask::WALKFL;
    Animator* backLeft = character->addAnimator("back left", "/Resources/Game/Character/Animations/Back Left.dae");
    backLeft->animatorBitMask = Bitmask::WALKBL;
    Animator* backRight = character->addAnimator("back right", "/Resources/Game/Character/Animations/Back Right.dae");
    backRight->animatorBitMask = Bitmask::WALKBR;
    Animator* roll = character->addAnimator("roll", "/Resources/Game/Character/Animations/Roll Fwd.dae");
    roll->animatorBitMask = Bitmask::ROLL;
    roll->speed = 1.5;
    roll->repeats = false;
    Animator* dragonAttack = character->addAnimator("dragon attack", "/Resources/Game/Character/Animations/DragonAttack.dae");
    dragonAttack->animatorBitMask = Bitmask::DRAGON_ATT;
    dragonAttack->repeats = false;
    Animator* castMagic1 = character->addAnimator("cast magic 1", "/Resources/Game/Character/Animations/CastMagic1.dae");
    castMagic1->animatorBitMask = Bitmask::MAGIC_CAST_1;
    castMagic1->repeats = false;
    Animator* castMagic2 = character->addAnimator("cast magic 2", "/Resources/Game/Character/Animations/CastMagic2.dae");
    castMagic2->animatorBitMask = Bitmask::MAGIC_CAST_2;
    castMagic2->repeats = false;
    Animator* castMagic3 = character->addAnimator("cast magic 3", "/Resources/Game/Character/Animations/CastMagic3.dae");
    castMagic3->animatorBitMask = Bitmask::MAGIC_CAST_3;
    castMagic3->repeats = false;
    Animator* damaged = character->addAnimator("damaged", "/Resources/Game/Character/Animations/Damaged.dae");
    damaged->animatorBitMask = Bitmask::DAMAGED;
    damaged->repeats = false;
    Animator* death = character->addAnimator("death", "/Resources/Game/Character/Animations/Death.dae");
    death->animatorBitMask = Bitmask::DEAD;
    death->repeats = false;
    death->clamps = true;
//    Animator* castMagic4 = character->addAnimator("cast magic 4", "/Resources/Game/Character/Animations/CastMagic4.dae");
//    character->modelNode->getAnimator("cast magic 4")->repeats = false;
//    Animator* castMagic5 = character->addAnimator("smash ground", "/Resources/Game/Character/Animations/Smash Ground.dae");
//    character->modelNode->getAnimator("smash ground")->repeats = false;
}


} // namespace ImportCharHelper
