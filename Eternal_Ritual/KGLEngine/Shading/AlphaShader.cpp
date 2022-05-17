//
//  AlphaShader.cpp
//
//  Created by futian Zhang on 5/3/22.
//  Updated by Kangming Yu on 5/16/22.
//

#include "KGLEngine/Shading/Shader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <glm/gtx/io.hpp>

#include "KGLEngine/Geometry/Geometry.hpp"
#include "KGLEngine/Engine.hpp"

using namespace std;
using namespace glm;


AlphaShader::AlphaShader(string shaderFile){
    this->fileName = shaderFile;
    string vertexShaderCode;
    string fragmentShaderCode;
    ifstream vertexShaderStream;
    ifstream fragmentShaderStream;
    vertexShaderStream.exceptions(ifstream::failbit | ifstream::badbit);
    fragmentShaderStream.exceptions(ifstream::failbit | ifstream::badbit);
    try {
        string vertexShaderFile = Engine::main->workingDirectory + shaderFile + ".vs";
        string fragmentShaderFile = Engine::main->workingDirectory + shaderFile + ".fs";
        vertexShaderStream.open(vertexShaderFile.c_str());
        fragmentShaderStream.open(fragmentShaderFile.c_str());
        stringstream vertexShader, fragmentShader;
        vertexShader << vertexShaderStream.rdbuf();
        fragmentShader << fragmentShaderStream.rdbuf();
        vertexShaderStream.close();
        fragmentShaderStream.close();
        vertexShaderCode = vertexShader.str();
        fragmentShaderCode = fragmentShader.str();
    }catch(ifstream::failure error) {
        cout << "\nFailed to load the shaders files: "
             << Engine::main->workingDirectory + shaderFile << "!\n" << endl;
        exit(1);
    }
    this->engineInitializeShader(vertexShaderCode, fragmentShaderCode);
}

AlphaShader* AlphaShader::copy(){
    AlphaShader* newShader = new AlphaShader(this->fileName);
    return newShader;
}

void AlphaShader::engineRenderShader(Geometry* geometry, unsigned int renderingMode) {
    if(this->clearDepthBuffer) {
        glDepthMask(GL_TRUE);
        glClear(GL_DEPTH_BUFFER_BIT);
    }
    if(Shader::currentBlendMode != this->blendMode) {
        Shader::currentBlendMode = this->blendMode;
        if(this->blendMode == 0) {
            glDisable(GL_BLEND);
        }else if(this->blendMode == 1) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        }else if(this->blendMode == 2) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
    }
    if(Shader::currentWriteToDepthBuffer != this->writeToDepthBuffer) {
        Shader::currentWriteToDepthBuffer = this->writeToDepthBuffer;
        if(this->writeToDepthBuffer) {
            glDepthMask(GL_TRUE);
        }else{
            glDepthMask(GL_FALSE);
        }
    }
    this->activateShader();
    
    // Adjust alpha
    if (currentAlpha != alpha){
        currentAlpha = alpha;
        this->setFloat("alpha", this->currentAlpha);
    }
    if (currenEmissiontColor != emissionColor){
        currenEmissiontColor = emissionColor;
                
        this->setVec3("defaultEmissionColor", this->currenEmissiontColor);
    }
    
    mat4 modelTransform = geometry->engineGetGeometryModelTransform();
    this->setBool("renderingMode", renderingMode);
    if(renderingMode == 1) {
        this->setMat4("lightSpaceMatrix", Engine::main->mainCameraNode->getDirectionalLightSpaceMatrix());
    }
    if(this->isUIShader) {
        if(Shader::currentDepthFunction != 1) {
            Shader::currentDepthFunction = 1;
            glDepthFunc(GL_ALWAYS);
        }
        mat4 projectionTransform = Engine::main->mainCameraNode->getOrthogonalProjectionTransform();
        this->setMat4("projectionTransform", projectionTransform);
        this->setMat4("modelProjectionTransform", projectionTransform * modelTransform);
    }else if(this->isParticleShader) {
        if(Shader::currentDepthFunction != 0) {
            Shader::currentDepthFunction = 0;
            glDepthFunc(GL_LESS);
        }
        this->setFloat("time", Engine::main->getTime());
        mat4 viewTransform = Engine::main->mainCameraNode->getViewTransform();
        mat4 projectionTransform = Engine::main->mainCameraNode->getProjectionTransform();
        this->setMat4("projectionTransform", projectionTransform);
        this->setMat4("viewTransform", viewTransform);
        this->setMat4("modelViewTransform", viewTransform * modelTransform);
    }else{
        if(Shader::currentDepthFunction != 0) {
            Shader::currentDepthFunction = 0;
            glDepthFunc(GL_LESS);
        }
        mat4 viewTransform = Engine::main->mainCameraNode->getViewTransform();
        mat4 projectionTransform = Engine::main->mainCameraNode->getProjectionTransform();
        mat4 viewProjectionTransform = projectionTransform * viewTransform;
        this->setFloat("frame.time", Engine::main->getTime());
        this->setMat4("frame.viewProjectionTransform", viewProjectionTransform);
        this->setVec3("frame.cameraPosition", Engine::main->mainCameraNode->getWorldPosition());
        this->setVec3("frame.cameraDirection", Engine::main->mainCameraNode->getFrontVectorInWorld());
        if(this->currentModelTransform != modelTransform) {
            this->currentModelTransform = modelTransform;
            this->setMat4("node.modelTransform", modelTransform);
            this->setMat4("node.normalTransform", transpose(inverse(modelTransform)));
        }
        this->setMat4("node.modelViewProjectionTransform", viewProjectionTransform * modelTransform);
        if(geometry->engineCheckWhetherGeometryHasBones() && geometry->engineCheckWhetherGeometryHasUpdatedSkeletalAnimations()) {
            this->setBool("hasBones", true);
            vector<mat4>* boneTransforms = geometry->engineGetGeometryBoneTransforms();
            for(unsigned int i = 0; i < BONES_LIMIT; i += 1) {
                this->setMat4("boneTransforms[" + to_string(i) + "]", (*boneTransforms)[i]);
            }
        }else{
            this->setBool("hasBones", false);
        }
        this->setBool("useShadowMap", false);
        unsigned int i = 0;
        unsigned int count = 0;
        while(count < LIGHTS_LIMIT && i < Engine::main->preparedLightNodes.size()) {
            if(geometry->engineCheckWhetherGeometryIsAffectedByLightNode(Engine::main->preparedLightNodes[i])) {
                Engine::main->preparedLightNodes[i]->engineConfigurateLightForShader(this, count);
                count += 1;
            }
            i += 1;
        }
        this->setInt("lightCount", count);
        geometry->affectedLightCount = count;
        for(unsigned int i = 0; i < Engine::main->preparedLightNodeShadows.size(); i += 1) {
            Engine::main->preparedLightNodeShadows[i]->engineConfigurateShadowForShader(this, i);
        }
        this->setInt("shadowCount", (unsigned int)Engine::main->preparedLightNodeShadows.size());
    }
    for(unsigned int i = 0; i < this->textures.size(); i += 1) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i]->data);
    }
    unsigned int amount = (unsigned int)geometry->engineGetGeometryInstanceCount();
    if(amount > 0) {
        this->setBool("enableInstancing", true);
        if(this->isUIShader) {
            glBindVertexArray(geometry->engineGetGeometryVertexArrays());
            glDrawArraysInstanced(GL_TRIANGLES, 0, 6, amount);
            glBindVertexArray(0);
        }else{
            glBindVertexArray(geometry->engineGetGeometryVertexArrays());
            glDrawElementsInstanced(GL_TRIANGLES, geometry->engineGetGeometryIndiceCount(), GL_UNSIGNED_INT, 0, amount);
            glBindVertexArray(0);
        }
    }else{
        this->setBool("enableInstancing", false);
        if(this->isUIShader) {
            glBindVertexArray(geometry->engineGetGeometryVertexArrays());
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }else{
            glBindVertexArray(geometry->engineGetGeometryVertexArrays());
            glDrawElements(GL_TRIANGLES, geometry->engineGetGeometryIndiceCount(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }
}

