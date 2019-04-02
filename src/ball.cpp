#include <cmath>
#include <algorithm>
#include "ball.h"
#include "game.h"

namespace bump {

Ball::Ball(Game& game)
: GameObject()
, m_game(game)
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

bool Ball::update(float timeDelta)
{
    float x = m_pos[0];
    float y = m_pos[1];
    float radius = m_shape.radius();
    float expectedX = x + m_speedX * timeDelta;
    float expectedY = y + m_speedY * timeDelta;

    float collideX, collideY, newSpeedX, newSpeedY, collideTime;
    bool collide = false;

    collide = collideWithBoundary(expectedX, expectedY, collideTime, collideX,
                                  collideY, newSpeedX, newSpeedY);

/*    float ballLeft = m_game.clampX(std::min(x, expectedX) - radius);
    float ballRight = m_game.clampX(std::max(x, expectedX) + radius);
    float ballBottom = m_game.clampY(std::min(y, expectedY) - radius);
    float ballTop = m_game.clampY(std::max(y, expectedY) + radius);*/

    if(!collide) {
        m_pos[0] = expectedX;
        m_pos[1] = expectedY;
    } else {
        m_pos[0] = collideX;
        m_pos[1] = collideY;
        m_speedX = newSpeedX;
        m_speedY = newSpeedY;
    }

    return m_pos[1] > -radius;
}

bool Ball::collideWithBoundary(float expectedX, float expectedY,
                               float& collideTime, float& collideX,
                               float& collideY, float& newSpeedX,
                               float& newSpeedY)
{
    float x = m_pos[0];
    float y = m_pos[1];
    float radius = m_shape.radius();
    bool collide = false;

    if(expectedX <= radius) {
        collideTime = (x - radius) / (-m_speedX);
        collideX = radius;
        collideY = y + m_speedY * collideTime;
        newSpeedX = -m_speedX;
        newSpeedY = m_speedY;
        collide = true;
    } else if(expectedX >= m_game.width() - radius) {
        collideTime = (m_game.width() - radius - x) / m_speedX;
        collideX = m_game.width() - radius;
        collideY = y + m_speedY * collideTime;
        newSpeedX = -m_speedX;
        newSpeedY = m_speedY;
        collide = true;
    }

    if(expectedY >= m_game.height() - radius) {
        float t1 = (m_game.height() - radius) / m_speedY;
        if(!collide || t1 < collideTime) {
            collideTime = (m_game.height() - radius - y) / m_speedY;
            collideX = x + m_speedX * collideTime;
            collideY = m_game.height() - radius;
            newSpeedX = m_speedX;
            newSpeedY = -m_speedY;
            collide = true;
        }
    }

    return collide;
}

bool Ball::collideWithBat(float expectedX, float expectedY,
                          float& collideTime, float& collideX,
                          float& collideY, float& newSpeedX,
                          float& newSpeedY)
{
}

} // end of namespace bump

