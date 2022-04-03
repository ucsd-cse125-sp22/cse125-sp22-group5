#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexUV;
out vec2 uv;
struct frame_data {
    mat4 viewTransform;
    //mat4 inverseViewTransform;
    mat4 projectionTransform;
    //mat4 viewProjectionTransform;
    //float time;
    //float sinTime;
    //float cosTime;
    //float random;
    //mat4 inverseProjectionTransform;
    //mat4 inverseViewProjectionTransform;
};
struct node_data {
    mat4 modelTransform;
    //mat4 inverseModelTransform;
    //mat4 modelViewTransform;
    //mat4 inverseModelViewTransform;
    //mat4 normalTransform;
    //mat4 modelViewProjectionTransform;
    //mat4 inverseModelViewProjectionTransform;
};
uniform frame_data frame;
uniform node_data node;
void main() {
    uv = vertexUV;
    gl_Position = frame.projectionTransform * frame.viewTransform * node.modelTransform * vec4(vertexPosition, 1.0);
}
