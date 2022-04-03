// Developed by Kelin.Lyu.
#ifndef Image_hpp
#define Image_hpp
#include "Toolkit/common.h"
#include "engine.hpp"
class Image final {
public:
    unsigned char* data;
    int width, height;
    int channelCount;
    Image(string file);
    ~Image();
};
#endif
