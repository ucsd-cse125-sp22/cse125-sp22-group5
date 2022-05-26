#version 330 core
in vec2 UV;
out vec4 color;
uniform sampler2D textureMap;
uniform float progess;
void main() {
    color = texture(textureMap, UV);
    if(color.a!=0){
        vec2 c = UV - vec2(0.5);
        vec2 v = vec2(0,0.5);
        if(UV.x>0.5){
            v = vec2(0,-0.5);
        }
        float angle = acos(dot(c,v)/(length(c)*length(v))) * (180/3.1415926);
        float p = angle/360;
        if(UV.x<0.5){
            p = p + 0.5;
        }
        if(progess<p){
            color.a=0;
        }
    }
}