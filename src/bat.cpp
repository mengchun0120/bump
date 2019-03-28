#include <stdexcept>
#include <cstring>
#include "log.h"
#include "config.h"
#include "bat.h"

namespace bump {

Bat::Bat(float gameWidth, float gameHeight)
: GameObject()
{
    Config& config = Config::getSingleton();

    if(!m_shape.init(0.0f, 0.0f, config.m_batWidth, config.m_batHeight)) {
        LOG_ERROR("Failed to initialize shape");
        throw std::runtime_error("Failed to initialize shape");
    }

    m_xBound = gameWidth - config.m_batWidth;
    m_pos[0] = (gameWidth - config.m_batWidth) / 2.0f;
    m_pos[1] = 0.0f;
    memcpy(m_fillColor, config.m_batColor, sizeof(m_fillColor));
}

Bat::~Bat()
{
}

void Bat::move(float newX)
{
    if(newX < 0.0f) {
        newX = 0.0f;
    } else if(newX > m_xBound) {
        newX = m_xBound;
    }
    m_pos[0] = newX;
}

void Bat::draw(BumpShaderProgram& program)
{
    m_shape.draw(program, m_pos, m_fillColor, nullptr, 0.0f);
}

} // end of namespace bump

