#ifndef INCLUDE_CONFIG
#define INCLUDE_CONFIG

#include <string>

namespace bump {

class Config {
public:
    static Config& getSingleton();

    static bool initSingleton(const char* fileName);

    ~Config();

public:
    int m_width;
    int m_height;
    std::string m_bumpVertexShaderFile;
    std::string m_bumpFragShaderFile;
    std::string m_title;

private:
    Config(const char* fileName);

    bool load(const char* fileName);
};

} // end of namespace bump

#endif
