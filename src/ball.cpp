#include <cmath>
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

bool Ball::collideVerticalLine(float& collideTime, float& newSpeedX, float& newSpeedY,
                               float x, float y0, float y1, float timeDelta)
{
    
}

bool Ball::collideHorizontalLine(float& collideTime, float& newSpeedX, float& newSpeedY,
                                 float y, float x0, float x1, float timeDelta)
{
    float r = m_shape.radius();
    float yc = m_pos[1];
    float xc = m_pos[0];
    float yDist = yc - y;
    float yDistAbs = (float)fabs(ydist);

    if(yDistAbs >= r) {
        if((yDist > 0.0f && m_speedY >= 0.0f) || (yDist < 0.0f && m_speedY <= 0.0f)) {
            return false;
        }

        float touchTime = (yDistAbs - r) / (float)fabs(m_speedY);
        if(touchTime > timeDelta) {
            return false;
        }

        float touchX = xc + touchTime * m_speedX;
        if(x0 <= touchX && touchX <= x1) {
            collideTime = touchTime;
            newSpeedX = m_speedX;
            newSpeedY = -m_speedY;
        } else {
            float checkX = (touchX > x1) ? x1 : x0;
            touchTime = (yc - yDistAbs * r / sqrt((xc-checkX)*(xc-checkX) + ydist*ydist)) / (-m_speedY);
            if(touchTime > timeDelta) {
                return false;
            }

            collideTime = touchTime;
            newSpeedX = -m_speedX;
            newSpeedY = -m_speedY;

        } else if(touchX < x0) {
        }

    } else if(ydist <= -r) {
        if(m_speedY <= 0) {
            return false;
        }

        float touchTime = (

    } else {
    }


    return true;
}

} // end of namespace bump
