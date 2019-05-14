#ifndef INCLUDE_CONFIG
#define INCLUDE_CONFIG

#include <string>
#include <vector>
#include "constants.h"

namespace bump {

class Config {
public:
    Config();

    ~Config();

    bool load(const char* fileName);

public:
    int m_width;
    int m_height;
    std::string m_bumpVertexShaderFile;
    std::string m_bumpFragShaderFile;
    std::string m_title;
    int m_pointerEventPoolSize;
    float m_batWidth;
    float m_batHeight;
    std::string m_batImage;
    float m_ballRadius;
    std::string m_ballImage;
    float m_boxWidth;
    float m_boxHeight;
    std::vector<std::string> m_boxImages;
    std::vector<int> m_boxMaxLife;
};

} // end of namespace bump

#endif
