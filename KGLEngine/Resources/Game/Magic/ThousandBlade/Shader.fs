// Developed by Kelin Lyu.
#version 330 core
in fragment_data {
    vec3 position;
    vec3 normal;
    vec2 UV;
    mat3 TBN;
    mat3 inverseTBN;
} fragment;
out vec4 color;
uniform sampler2D diffuseMap;
uniform vec3 defaultEmissionColor;
uniform float alpha;

void main() {
    vec2 UV = fragment.UV;
    color = texture(diffuseMap, UV);
    if(color.a < 0.1) {
        discard;
    }
    color.a *= alpha;
    color.rgb += defaultEmissionColor;
}
