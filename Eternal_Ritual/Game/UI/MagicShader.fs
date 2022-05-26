#version 330 core

#define M_PI 3.1415926535897932384626433832795

in vec2 UV;
out vec4 color;

uniform float progess;

uniform float alpha;
uniform vec4 defaultColor;
uniform bool useTextureMap;
uniform sampler2D textureMap;
uniform vec3 defaultMultiplyColor;
uniform bool useMultiplyTextureMap;
uniform sampler2D multiplyTextureMap;
uniform float multiplyIntensity;
uniform vec3 defaultEmissionColor;
uniform bool useEmissionTextureMap;
uniform sampler2D emissionTextureMap;
uniform float emissionIntensity;
void main() {

    color = defaultColor;
    if(useTextureMap) {
        color = texture(textureMap, UV);
    }
    vec3 multiplyColor = defaultMultiplyColor;
    if(useMultiplyTextureMap) {
        multiplyColor = texture(multiplyTextureMap, UV).rgb;
    }
    vec3 inverseMultiplyColor = vec3(1.0f) - multiplyColor;
    multiplyColor = vec3(1.0f) - inverseMultiplyColor * multiplyIntensity;
    color.rgb *= multiplyColor;
    vec3 emissionColor = defaultEmissionColor;
    if(useEmissionTextureMap) {
        emissionColor = texture(emissionTextureMap, UV).rgb;
    }
    emissionColor *= emissionIntensity;
    color.rgb += emissionColor;
    color.a *= alpha;

    //if(alpha!=0){
        //vec2 v1 = UV - vec2(0.5f);
        //vec2 v2 = vec2(0.0f,0.5f);
        //float angle = acos(dot(v1,v2)/(length(v1)*length(v2)));
        //float p = angle/ 2 * M_PI;
        //if(p<progess){
            //color.a *= 0;    
		//}
	//}
}