#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 vertexUV;
layout (location = 2) in vec3 vertexNormal;
layout (location = 3) in vec3 vertexTangent;
layout (location = 4) in vec3 vertexBitangent;
layout (location = 5) in vec2 birthTimeAndDuration;
layout (location = 6) in vec3 initialPosition;
layout (location = 7) in vec3 initialSpeed;
layout (location = 8) in vec4 accelerationData;
layout (location = 9) in vec3 rotationData;
layout (location = 10) in vec3 rotationSpeedData;
layout (location = 11) in vec3 scaleData;
layout (location = 12) in vec3 scaleSpeedData;
layout (location = 13) in vec2 spriteSheetAnimationData;
out fragment_data {
    float progress;
    vec2 UV;
    vec2 spriteSheetAnimationData;
} fragment;
uniform float time;
uniform mat4 projectionTransform;
uniform mat4 viewTransform;
uniform mat4 modelViewTransform;
uniform bool useLocalSpace;
mat4 rotationMatrix(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    
    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}
void main() {
    float progress = time - birthTimeAndDuration.x;
    if(progress > birthTimeAndDuration.y) {
        gl_Position = vec4(0.0f);
        return;
    }
    float accelerationFactor = progress * progress * 0.5f;
    vec4 particlePosition = vec4(initialPosition, 1.0f);
    particlePosition.xyz += initialSpeed * progress;
    particlePosition.xyz += initialSpeed * accelerationData.w * accelerationFactor;
    particlePosition.xyz += accelerationData.xyz * accelerationFactor;
    vec4 localVertexPosition = vec4(vertexPosition, 1.0f);
    localVertexPosition.xyz *= max(vec3(0.0f), scaleData + scaleSpeedData * progress);
    vec3 rotation = rotationData + rotationSpeedData * progress;
    localVertexPosition *= rotationMatrix(vec3(0, 1, 0), rotation.y) * rotationMatrix(vec3(0, 0, 1), rotation.z) * rotationMatrix(vec3(1, 0, 0), rotation.x);
    if(useLocalSpace) {
        gl_Position = projectionTransform * (modelViewTransform * particlePosition + localVertexPosition);
    }else{
        gl_Position = projectionTransform * (viewTransform * particlePosition + localVertexPosition);
    }
    fragment.progress = progress / birthTimeAndDuration.y;
    fragment.UV = vertexUV;
    fragment.spriteSheetAnimationData = spriteSheetAnimationData;
}
