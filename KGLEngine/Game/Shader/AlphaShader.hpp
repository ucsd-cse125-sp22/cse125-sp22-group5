//
//  AlphaShader.hpp
//  KGLEngine
//
//  Created by futian Zhang on 5/3/22.
//

#ifndef AlphaShader_hpp
#define AlphaShader_hpp

#include "../includes.hpp"

class AlphaShader : public Shader {
protected:
    float currentAlpha;
    vec3 currenEmissiontColor;
public:
    AlphaShader(string shaderFile);
    string fileName;
    float alpha;
    vec3 emissionColor;
    AlphaShader* copy();
    void engineRenderShader(Geometry* geometry, unsigned int renderingMode) override;
};

#endif /* AlphaShader_hpp */
