#ifndef INCLUDE_TEXTURE
#define INCLUDE_TEXTURE

#include <string>

namespace bump {

class Texture {
public:
    Texture();

    Texture(const std::string& imageFile);

    virtual ~Texture();

    bool load(const std::string& imageFile);

    unsigned int textureId() const
    {
        return m_textureId;
    }

    int width() const
    {
        return m_width;
    }

    int height() const
    {
        return m_height;
    }

    int numChannels() const
    {
        return m_numChannels;
    }

private:
    unsigned int m_textureId;
    int m_width, m_height, m_numChannels;
};

} // end of namespace bump

#endif

