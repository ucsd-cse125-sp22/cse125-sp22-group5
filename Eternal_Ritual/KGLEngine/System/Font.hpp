// Developed by Kelin Lyu.
#ifndef Font_hpp
#define Font_hpp

#include <vector>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "KGLEngine/Shading/Texture.hpp"


struct FontCharacter final {
public:
    Texture* texture;
    glm::vec2 size;
    glm::vec2 bearing;
    float advance;
};
class Font final {
public:
    std::vector<FontCharacter*> characters;
public:
    Font(FT_Face font);
    ~Font();
    FontCharacter* engineGetFontCharacter(unsigned char character);
};
#endif
