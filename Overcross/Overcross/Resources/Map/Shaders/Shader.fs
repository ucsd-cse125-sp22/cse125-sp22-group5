#version 330 core
in vec2 uv;
out vec4 color;
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

uniform sampler2D diffuse;
uniform sampler2D normal;

void main() {
    vec4 result = texture(diffuse, uv);
    if(result.a < 0.5) {
        discard;
    }
    color = texture(diffuse, uv);
}
