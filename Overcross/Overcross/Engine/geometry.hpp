// Developed by Kelin.Lyu.
#ifndef Geometry_hpp
#define Geometry_hpp
#include "Toolkit/common.h"
#include "engine.hpp"
#define MAX_BONE_INFLUENCE 4
class Shader;
struct Vertex {
    vec3 position;
    vec3 normal;
    vec2 uv;
    vec3 tangent;
    vec3 bitangent;
    int boneIDs[MAX_BONE_INFLUENCE];
    float weights[MAX_BONE_INFLUENCE];
};
class Geometry final {
private:
    Shader* shader;
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    unsigned int VAO, VBO, EBO;
public:
    Geometry(vector<Vertex> vertices, vector<unsigned int> indices);
    void setShader(Shader* shader);
    void render(mat4 modelTransform);
    ~Geometry();
};
#endif
