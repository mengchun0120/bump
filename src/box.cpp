#include <stdexcept>
#include "box.h"

namespace bump {

Rectangle Box::k_shape;

float Box::k_colors[TYPE_COUNT][Constants::NUM_FLOATS_COLOR] = {
    {0.0f, 1.0f, 0.0f, 1.0f},
    {1.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 1.0f, 1.0f},
    {1.0f, 0.0f, 1.0f, 1.0f}
};

int Box::k_maxLife[TYPE_COUNT] = {
    1, 2, 4, 8
};

void Box::initShape()
{
    if(k_shape.numVertices() == 0) {
        k_shape.init(0.0f, 0.0f, 80.0f, 20.0f);
    }
}

Box::Box(float x, float y, int type)
{
    if(type < 0 || type >= TYPE_COUNT) {
        throw std::runtime_error("type out of bounds");
    }

    m_type = type;
    m_pos[0] = x;
    m_pos[1] = y;
    m_life = k_maxLife[type];
    for(unsigned int i = 0; i < Constants::NUM_FLOATS_COLOR; ++i) {
        m_color[i] = k_colors[m_type][i];
    }
}

Box::~Box()
{
}

void Box::draw(BumpShaderProgram& program)
{
    k_shape.draw(program, m_pos, m_color, nullptr, 0.0f);
}

bool Box::onHit()
{
    if(m_life > 0) {
        --m_life;
        m_color[3] -= 1.0f / (float)k_maxLife[m_type];
    }

    return m_life > 0;
}

} // end of namespace bump
