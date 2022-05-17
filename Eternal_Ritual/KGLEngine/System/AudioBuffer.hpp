// Developed by Kelin Lyu.
#ifndef AudioBuffer_hpp
#define AudioBuffer_hpp

#include <vector>
#include <string>
#include <SFML/Audio.hpp>

class AudioBuffer final {
private:
    std::vector<sf::SoundBuffer> buffers;
    std::vector<unsigned int> previousBufferIndices;
public:
    AudioBuffer(std::string file);
    AudioBuffer(std::string file, std::string extension, unsigned int startIndex, unsigned int endIndex);
    ~AudioBuffer();
    sf::SoundBuffer* engineGetAudioBuffer();
};
#endif
