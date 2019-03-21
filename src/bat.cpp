#include "bat.h"

namespace bump {

Bat::Bat(GLfloat gameWidth, GLfloat gameHeight)
: GameObject((gameWidth-100.0f)/2.0f, 0.0f)
, m_xBound(gameWidth-100.0f)
, m_shape(0.0f, 0.0f, 100.0f, 10.0f)
, m_fillColor{1.0f, 0.0f, 1.0f, 1.0f}
{
}

Bat::~Bat()
{
}

void Bat::draw(BumpShaderProgram& program)
{
    m_shape.draw(program, m_pos, m_fillColor, nullptr, 0.0f);
}

} // end of namespace bump

