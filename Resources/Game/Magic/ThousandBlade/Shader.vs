// Developed by Kelin Lyu.
#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexUV;
layout (location = 3) in vec3 vertexTangent;
layout (location = 4) in vec3 vertexBitangent;
out fragment_data {
    vec3 position;
    vec3 normal;
    vec2 UV;
    mat3 TBN;
    mat3 inverseTBN;
} fragment;
struct frame_data {
    mat4 viewProjectionTransform;
    vec3 cameraPosition;
    vec3 cameraDirection;
};
struct node_data {
    mat4 modelTransform;
    mat4 normalTransform;
    mat4 modelViewProjectionTransform;
};
uniform frame_data frame;
uniform node_data node;
void main() {
    mat4 modelTransform = node.modelTransform;
    mat4 normalTransform = node.normalTransform;
    mat4 modelViewProjectionTransform = node.modelViewProjectionTransform;
    
    vec4 localPosition = vec4(vertexPosition, 1.0f);
    gl_Position = modelViewProjectionTransform * localPosition;
    fragment.UV = vertexUV;
}
