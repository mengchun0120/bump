#include <cmath>
#include <ctime>
#include <cstdlib>
#include "collide.h"
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

void Ball::init(float x, float y, float speed)
{
    m_pos[0] = x;
    m_pos[1] = y;
    m_speed = speed;

    float factor = (float)(sqrt(2.0) / 2.0);
    bool moveLeft = ((float)rand() / (float)RAND_MAX) > 0.5f;
    m_speedX = moveLeft ? -m_speed * factor : m_speed * factor;
    m_speedY = speed * factor;
}

void Ball::draw(BumpShaderProgram& program)
{
    m_shape.draw(program, m_pos, m_color, nullptr, 0.0f);
}

bool Ball::update(float timeDelta)
{
    CollideImpact finalImpact, impact;
    bool collide = false;

    collide = collideBoundary(finalImpact, timeDelta);

    const Bat& bat = m_game.bat();
    if(collideRect(impact, bat.x(), bat.y(), bat.right(),
                   bat.top(), timeDelta)) {

        if(collide) {
            if(finalImpact.m_collideTime > impact.m_collideTime) {
                finalImpact = impact;
            }
        } else {
            finalImpact = impact;
            collide = true;
        }
    }

    if(!collide) {
        m_pos[0] += m_speedX * timeDelta;
        m_pos[1] += m_speedY * timeDelta;
    } else {
        m_pos[0] = finalImpact.m_newCenterX;
        m_pos[1] = finalImpact.m_newCenterY;
        m_speedX = finalImpact.m_newSpeedX;
        m_speedY = finalImpact.m_newSpeedY;
    }

    return m_pos[1] > -radius();
}

bool Ball::collideBoundary(CollideImpact& impact, float timeDelta)
{
    float tx = m_pos[0];
    float ty = m_pos[1];
    float radius = m_shape.radius();
    CollideResult result;

    result = circleCollideLine(impact.m_collideTime,
                               impact.m_newCenterX,
                               tx, radius, m_speedX,
                               0, true,
                               timeDelta);

    if(result == COLLIDE_INTIME) {
        impact.m_newCenterY = ty + m_speedY * impact.m_collideTime;
        impact.m_newSpeedX = -m_speedX;
        impact.m_newSpeedY = m_speedY;
        return true;
    }

    result = circleCollideLine(impact.m_collideTime,
                               impact.m_newCenterX,
                               tx, radius, m_speedX,
                               m_game.width(), false,
                               timeDelta);

    if(result == COLLIDE_INTIME) {
        impact.m_newCenterY = ty + m_speedY * impact.m_collideTime;
        impact.m_newSpeedX = -m_speedX;
        impact.m_newSpeedY = m_speedY;
        return true;
    }

    result = circleCollideLine(impact.m_collideTime,
                               impact.m_newCenterY,
                               ty, radius, m_speedY,
                               m_game.height(), false,
                               timeDelta);

    if(result == COLLIDE_INTIME) {
        impact.m_newCenterX = tx + m_speedX * impact.m_collideTime;
        impact.m_newSpeedX = m_speedX;
        impact.m_newSpeedY = -m_speedY;
        return true;
    }

    return false;
}

bool Ball::collideRect(CollideImpact& impact,
                       float left, float bottom, float right, float top,
                       float timeDelta)
{
    float tx = m_pos[0];
    float ty = m_pos[1];
    float tradius = m_shape.radius();
    CollideResult result;
    float collideX, collideY;

    result = circleCollideRect(impact.m_collideTime,
                               impact.m_newCenterX, impact.m_newCenterY,
                               collideX, collideY,
                               tx, ty, tradius,
                               m_speedX, m_speedY,
                               left, bottom, right, top,
                               timeDelta);

    if(result == COLLIDE_NOTHING) {
        return false;
    }

    switch(result) {
    case COLLIDE_HORIZONTAL:
        impact.m_newSpeedX = m_speedX;
        impact.m_newSpeedY = -m_speedY;
        break;

    case COLLIDE_VERTICAL:
        impact.m_newSpeedX = -m_speedX;
        impact.m_newSpeedY = m_speedY;
        break;

    case COLLIDE_POINT:
        {
            float deltaX = impact.m_newCenterX - collideX;
            float deltaY = impact.m_newCenterY - collideY;
            float dist = sqrt(deltaX * deltaX + deltaY * deltaY);
            impact.m_newSpeedX = m_speed * deltaX / dist;
            impact.m_newSpeedY = m_speed * deltaY / dist;
        }
        break;
    }

    return true;
}

} // end of namespace bump

