#include <stdexcept>
#include <cstring>
#include "log.h"
#include "config.h"
#include "bat.h"

namespace bump {

Bat::Bat(GLfloat gameWidth, GLfloat gameHeight)
: GameObject()
{
    Config& config = Config::getSingleton();

    LOG_INFO("batWidth=%f batHeight=%f", config.m_batWidth, config.m_batHeight);

    if(!m_shape.init(0.0f, 0.0f, config.m_batWidth, config.m_batHeight)) {
        LOG_ERROR("Failed to initialize shape");
        throw std::runtime_error("Failed to initialize shape");
    }

    m_xBound = gameWidth - config.m_batWidth;
    x() = (gameWidth - config.m_batWidth) / 2.0f;
    y() = 0.0f;
    memcpy(m_fillColor, config.m_batColor, sizeof(m_fillColor));

    LOG_INFO("bat fillColor: %f %f %f %f", m_fillColor[0], m_fillColor[1],
             m_fillColor[2], m_fillColor[3]);
}

Bat::~Bat()
{
}

void Bat::move(GLfloat newX)
{
    if(newX < 0.0f) {
        newX = 0.0f;
    } else if(newX > m_xBound) {
        newX = m_xBound;
    }
    x() = newX;
}

void Bat::draw(BumpShaderProgram& program)
{
    m_shape.draw(program, m_pos, m_fillColor, nullptr, 0.0f);
}

} // end of namespace bump

