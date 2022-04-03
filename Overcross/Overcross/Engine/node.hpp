// Developed by Kelin.Lyu.
#ifndef Node_hpp
#define Node_hpp
#include "Toolkit/common.h"
#include "engine.hpp"
class Geometry;
class Node {
private:
    void processNode(aiNode* node, const aiScene* scene);
    Geometry* generateGeometry(aiMesh* mesh, const aiScene* scene);
    bool hasCamera;
    float cameraField;
    float cameraNear;
    float cameraFar;
public:
    vec3 position;
    vec3 eulerAngles;
    vec3 scale;
    bool isHidden;
    Node();
    vector<Geometry*> geometries;
    void loadGeometry(string file);
    void setCamera(float field, float near, float far);
    void render();
    mat4 getModelTransform();
    vec3 getWorldUp();
    vec3 getFront();
    vec3 getRight();
    vec3 getUp();
    mat4 getCameraProjectionTransform();
    mat4 getCameraViewTransform();
    ~Node();
};
#endif
