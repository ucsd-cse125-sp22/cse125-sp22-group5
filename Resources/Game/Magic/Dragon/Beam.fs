// Developed by Kelin Lyu.
#version 330 core
const int LIGHTS_LIMIT = 30;
const int SHADOWS_LIMIT = 6;
in fragment_data {
    vec3 position;
    vec3 normal;
    vec2 UV;
    mat3 TBN;
    mat3 inverseTBN;
    vec4 lightSpacePositions[SHADOWS_LIMIT];
    vec3 worldPosition;
} fragment;
out vec4 color;
struct frame_data {
    float time;
    mat4 viewProjectionTransform;
    vec3 cameraPosition;
    vec3 cameraDirection;
};
struct node_data {
    mat4 modelTransform;
    mat4 normalTransform;
    mat4 modelViewProjectionTransform;
};
struct light_data {
    int type;
    vec3 colorFactor;
    vec3 highlightFactor;
    vec3 position;
    vec3 direction;
    float attenuationExponent;
    float range;
    float penetrationRange;
    float innerAngle;
    float outerAngle;
    int shadowIndex;
};
struct shadow_data {
    int type;
    sampler2D shadowMap;
    mat4 lightSpaceMatrix;
    float bias;
    int samples;
};
uniform frame_data frame;
uniform node_data node;
uniform light_data lights[LIGHTS_LIMIT];
uniform int lightCount;
uniform shadow_data shadows[SHADOWS_LIMIT];
uniform int shadowCount;
uniform int renderingMode;

uniform sampler2D beamMap;
uniform float range;
uniform float time;

uniform vec3 start;
uniform vec3 end;

void main() {
    if(renderingMode == 1) {
        return;
    }
    vec2 UV = fragment.UV;
    
    float factor1 = (sin(time * 5.0f) * 0.2f + 0.6f) * 0.2f;
    float factor2 = (cos(time * 5.0f) * 0.2f + 0.6f) * 0.2f;
    
    vec2 UV1 = UV * vec2(1.0f, range * 0.1f) + vec2(0.0f, -time * 3.0f);
    float component1 = texture(beamMap, UV1).r;
    component1 = component1 * (1.0f - factor1 - factor2);
    
    vec2 UV2 = UV * vec2(1.0f, range * 0.2f) + vec2(0.0f, -time * 2.0f);
    float component2 = texture(beamMap, UV2).g;
    component2 = component2 * factor1;
    
    vec2 UV3 = UV * vec2(1.0f, range * 0.4f) + vec2(0.0f, -time * 1.0f);
    float component3 = texture(beamMap, UV3).b;
    component3 = component3 * factor2;
    
    float sum = component1 + component2 + component3;
    sum = sum * 1.5f;
    
    float intensity = 2.0f;
    
    float minLength = min(1.0f, range * 0.5f);
    float length1 = length(fragment.worldPosition.xyz - start);
    float length2 = length(fragment.worldPosition.xyz - end);
    
    if(length1 < minLength) {
        intensity = max(0.0f, (length1 - minLength * 0.1f) / (minLength * 0.9f));
    }else if(length2 < minLength) {
        intensity = max(0.0f, (length2 - minLength * 0.5f) / (minLength * 0.5f));
    }
    
    color = vec4(vec3(sum, sum * 0.5f, 0.1f), intensity);
}
