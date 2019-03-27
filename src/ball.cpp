#include "ball.h"

namespace bump {

Ball::Ball()
: GameObject()
, m_shape(0.0f, 0.0f, 10.0f, 40)
, m_color{0.0f, 1.0f, 0.0f, 1.0f}
{
}

Ball::~Ball()
{
}

void Ball::init(float x, float y, float speedX, float speedY)
{
    m_pos[0] = x;
    m_pos[1] = y;
    m_speedX = speedX;
    m_speedY = speedY;
}


void Ball::draw(BumpShaderProgram& program)
{
    m_shape.draw(program, m_pos, m_color, nullptr, 0.0f);
}

void Ball::update(Game& game, float timeDelta)
{
}

} // end of namespace bump
