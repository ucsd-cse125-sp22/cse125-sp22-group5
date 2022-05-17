// Developed by Kelin Lyu.
#ifndef Texture_hpp
#define Texture_hpp

#include <string>


class Texture final {
public:
    unsigned int data;
    Texture() = default;
    Texture(std::string file);
    Texture(std::string file, float maxAnisotropy, bool generateMipmaps);
    Texture(std::string right, std::string left,
            std::string top, std::string bottom,
            std::string front, std::string back,
            float maxAnisotropy);
    Texture(int width, int height, unsigned char* buffer);
    ~Texture();
};
#endif
