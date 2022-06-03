// Developed by Kelin Lyu.
#ifndef FontLibrary_hpp
#define FontLibrary_hpp

#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "KGLEngine/System/Font.hpp"


class FontLibrary final {
public:
    FT_Library* fontLibrary;
public:
    FontLibrary();
    Font* loadFontFile(std::string file, int heightResolution);
    ~FontLibrary();
};
#endif
