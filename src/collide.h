#ifndef INCLUDE_COLLIDE
#define INCLUDE_COLLIDE

namespace bump {

struct CollideImpact {
    float m_Time;
    float m_newX;
    float m_newY;
    float m_newSpeedX;
    float m_newSpeedY;
};

bool overlapRect(float left1, float bottom1, float right1, float top1,
                 float left2, float bottom2, float right2, float top2);

bool circleCollideRect(float& collideTime, float& newCenterX, float& newCenterY,
                       float& newSpeedX, float& newSpeedY, float centerX,
                       float centerY, float radius, float speedX, float speedY,
                       float left, float bottom, float right, float top, float timeDelta);


} // end of namespace bump

#endif

