// Developed by Kelin Lyu.
#include "KGLEngine/Geometry/Geometry.hpp"

#include <GL/glew.h>

#include "KGLEngine/Toolkit/assimp_helper.h"

using namespace std;
using namespace glm;


Particle3DRenderer::Particle3DRenderer(unsigned int amount, aiMesh* mesh) {
    this->engineInitializeGeometry();
    this->particleAmount = amount;
    struct Particle3DVertex {
        vec3 position;
        vec2 uv;
        vec3 normal;
        vec3 tangent;
        vec3 bitangent;    };
    vector<Particle3DVertex> vertices;
    vector<unsigned int> indices;
    for(unsigned int i = 0; i < mesh->mNumVertices; i += 1) {
        Particle3DVertex vertex;
        vertex.position = assimp_helper::getVec3(mesh->mVertices[i]);
        if(mesh->HasNormals()) {
            vertex.normal = assimp_helper::getVec3(mesh->mNormals[i]);
        }
        else {
            vertex.normal = vec3(0);
        }
        if(mesh->mTextureCoords[0]) {
            vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.uv = vec;
            vertex.tangent = assimp_helper::getVec3(mesh->mTangents[i]);
            vertex.bitangent = assimp_helper::getVec3(mesh->mBitangents[i]);
        }else{
            vertex.uv = vec2(0.0f);
            vertex.tangent = vec3(0);
            vertex.bitangent = vec3(0);
        }
        vertices.push_back(vertex);
    }
    for(unsigned int i = 0; i < mesh->mNumFaces; i += 1) {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j += 1) {
            indices.push_back(face.mIndices[j]);
        }
    }
    this->indiceCount = (unsigned int)indices.size();
    glGenVertexArrays(1, &this->vertexArrays);
    glGenBuffers(1, &this->vertexBuffers);
    glGenBuffers(1, &this->elementBuffers);
    glBindVertexArray(this->vertexArrays);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffers);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Particle3DVertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBuffers);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle3DVertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Particle3DVertex), (void*)offsetof(Particle3DVertex, uv));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Particle3DVertex), (void*)offsetof(Particle3DVertex, normal));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Particle3DVertex), (void*)offsetof(Particle3DVertex, tangent));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Particle3DVertex), (void*)offsetof(Particle3DVertex, bitangent));
    for(unsigned int i = 0; i < this->particleAmount; i += 1) {
        Particle3DData data;
        data.birthTimeAndDuration = vec2(0.0f);
        data.initialPosition = vec3(0.0f);
        data.initialSpeed = vec3(0.0f);
        data.accelerationData = vec4(0.0f);
        data.rotationData = vec3(0.0f);
        data.rotationSpeedData = vec3(0.0f);
        data.scaleData = vec3(0.0f);
        data.scaleSpeedData = vec3(0.0f);
        data.spriteSheetAnimationData = vec2(0.0f);
        this->dataVector.push_back(data);
    }
    glGenBuffers(1, &this->dataBuffers);
    glBindBuffer(GL_ARRAY_BUFFER, this->dataBuffers);
    glBufferData(GL_ARRAY_BUFFER, this->particleAmount * sizeof(Particle3DData), &this->dataVector[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(Particle3DData), (void*)0);
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, sizeof(Particle3DData), (void*)offsetof(Particle3DData, initialPosition));
    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, sizeof(Particle3DData), (void*)offsetof(Particle3DData, initialSpeed));
    glEnableVertexAttribArray(8);
    glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(Particle3DData), (void*)offsetof(Particle3DData, accelerationData));
    glEnableVertexAttribArray(9);
    glVertexAttribPointer(9, 3, GL_FLOAT, GL_FALSE, sizeof(Particle3DData), (void*)offsetof(Particle3DData, rotationData));
    glEnableVertexAttribArray(10);
    glVertexAttribPointer(10, 3, GL_FLOAT, GL_FALSE, sizeof(Particle3DData), (void*)offsetof(Particle3DData, rotationSpeedData));
    glEnableVertexAttribArray(11);
    glVertexAttribPointer(11, 3, GL_FLOAT, GL_FALSE, sizeof(Particle3DData), (void*)offsetof(Particle3DData, scaleData));
    glEnableVertexAttribArray(12);
    glVertexAttribPointer(12, 3, GL_FLOAT, GL_FALSE, sizeof(Particle3DData), (void*)offsetof(Particle3DData, scaleSpeedData));
    glEnableVertexAttribArray(13);
    glVertexAttribPointer(13, 2, GL_FLOAT, GL_FALSE, sizeof(Particle3DData), (void*)offsetof(Particle3DData, spriteSheetAnimationData));
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    glVertexAttribDivisor(7, 1);
    glVertexAttribDivisor(8, 1);
    glVertexAttribDivisor(9, 1);
    glVertexAttribDivisor(10, 1);
    glVertexAttribDivisor(11, 1);
    glVertexAttribDivisor(12, 1);
    glVertexAttribDivisor(13, 1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
Particle3DRenderer::~Particle3DRenderer() {
    glDeleteBuffers(1, &this->dataBuffers);
    this->dataVector.clear();
}
void Particle3DRenderer::engineResetAllParticleData() {
    for(unsigned int i = 0; i < this->particleAmount; i += 1) {
        this->dataVector[i].birthTimeAndDuration = vec2(0.0f);
    }
}
void Particle3DRenderer::engineRenderGeometry(unsigned int renderingMode) {
    glDisable(GL_CULL_FACE);
    glBindBuffer(GL_ARRAY_BUFFER, this->dataBuffers);
    glBufferData(GL_ARRAY_BUFFER, this->particleAmount * sizeof(Particle3DData), &this->dataVector[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    this->shader->engineRenderShader(this, renderingMode);
    this->updated = false;
    this->prepared = false;
}
Particle3DData* Particle3DRenderer::engineGetParticleData(bool front) {
    if(front) {
        Particle3DData data = this->dataVector[0];
        this->dataVector.erase(this->dataVector.begin());
        this->dataVector.push_back(data);
        return(&this->dataVector[(unsigned int)this->dataVector.size() - 1]);
    }
    Particle3DData data = this->dataVector[(unsigned int)this->dataVector.size() - 1];
    this->dataVector.erase(this->dataVector.end() - 1);
    this->dataVector.insert(this->dataVector.begin(), data);
    return(&this->dataVector[0]);
}
unsigned int Particle3DRenderer::engineGetGeometryInstanceCount() {
    return(this->particleAmount);
}
