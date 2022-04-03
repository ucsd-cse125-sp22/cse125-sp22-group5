// Developed by Kelin.Lyu.
#ifndef Texture_hpp
#define Texture_hpp
#include "Toolkit/common.h"
#include "engine.hpp"
class Texture final {
public:
    unsigned int data;
    Texture(string file, GLint wrapMode);
    ~Texture();
};
#endif
