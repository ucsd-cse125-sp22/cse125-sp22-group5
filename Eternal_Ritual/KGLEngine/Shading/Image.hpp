// Developed by Kelin Lyu.
#ifndef Image_hpp
#define Image_hpp

#include <string>


class Image final {
public:
    unsigned char* data;
    int width;
    int height;
    int channelCount;
    Image(std::string file);
    ~Image();
};
#endif
