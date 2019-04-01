#include <cmath>
#include <algorithm>
#include "ball.h"
#include "game.h"

namespace bump {

struct CollideImpact {
    float m_Time;
    float m_newX;
    float m_newY;
    float m_newSpeedX;
    float m_newSpeedY;
};

enum CollideResult {
    COLLIDE_LINE_ONLY,
    COLLIDE_TRUELY,
    COLLIDE_NOTHING
};

bool overlapRect(float left1, float bottom1, float right1, float top1,
                 float left2, float bottom2, float right2, float top2)
{
    return (left1 < right2 && right1 > left2 && bottom1 < top2 && top1 > bottom2;
}

CollideResult collideLines(float& collideTime, float& collidePos,
                           float& collidePosOther, float& newSpeed,
                           float& newSpeedOther, bool& collideLower,
                           float center, float centerOther, float radius,
                           float speed, float speedOther,
                           float lowerBound, float upperBound,
                           float lowerBoundOther, float upperBoundOther,
                           float timeDelta)
{
    bool collideLine = false;

    if(center + radius <= lowerBound && speed > 0) {
        float time = (lowerBound - center - radius) / speed;
        if(time <= timeDelta) {
            collideTime = time;
            collidePos = lowerBound - radius;
            collideLine = true;
        }
    } else if(center - radius >= upperBound && speed < 0) {
        float time = (center - radius - upperBound) / (-speed);
        if(time <= timeDelta) {
            collideTime = time;
            collidePos = upperBound + radius;
            collideLine = true;
        }
    }

    if(collideLine) {
        float posOther = centerOther + speedOther * collideTime;
        if(posOther >= lowerBoundOther && posOther <= upperBoundOther) {
            collidePosOther = posOther;
            newSpeed = -speed;
            newSpeedOther = speedOther;
            return COLLIDE_TRUELY;
        }
    }

    return collideLine ? COLLIDE_LINE_ONLY : COLLIDE_NOTHING;
}

bool circleCollideRect(CollideImpact& impact, float centerX, float centerY, float radius,
                       float speedX, float speedY, float left, float bottom, float right,
                       float top, float timeDelta)
{
    bool collide = false;
    CollideResult collideH = collideLines(impact.m_collideTime, impact.m_newX,
                                          impact.m_newY, impact.m_newSpeedX,
                                          impact.m_newSpeedY, centerX, centerY, radius,
                                          speedX, speedY, left, right,
                                          bottom, upper, timeDelta);

    if(collideH == COLLIDE_TRUELY) {
        return true;
    }

    CollideResult collideV = collideLines(impact.m_collideTime, impact.m_newY,
                                          impact.m_newX, impact.m_newSpeedY,
                                          impact.m_newSpeedX, centerY, centerX, radius,
                                          speedY, speedX, bottom, upper,
                                          left, right, timeDelta);

    if(collideV == COLLIDE_TRUELY) {
        return true;
    }

    if(collideH == COLLIDE_LINE_ONLY && collideV == COLLIDE_LINE_ONLY) {

    }
}

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

    float ballLeft = m_game.clampX(std::min(x, expectedX) - radius);
    float ballRight = m_game.clampX(std::max(x, expectedX) + radius);
    float ballBottom = m_game.clampY(std::min(y, expectedY) - radius);
    float ballTop = m_game.clampY(std::max(y, expectedY) + radius);

    if(ballLeft != ballRight && ballBottom != ballTop) {
        const Bat& bat = m_game.bat();
        if(collideRect(ballLeft, ballBottom, ballRight, ballTop,
                       bat.x(), bat.y(), bat.x() + bat.width(), bat.y() + bat.height())) {
        }
    }

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

