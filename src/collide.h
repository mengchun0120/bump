#ifndef INCLUDE_COLLIDE
#define INCLUDE_COLLIDE

namespace bump {

enum CollideResult {
    COLLIDE_NOTHING,
    COLLIDE_INTIME,
    COLLIDE_ALREADY,
    COLLIDE_POTENTIAL,
    COLLIDE_CONTAINED,
    COLLIDE_HORIZONTAL,
    COLLIDE_VERTICAL,
    COLLIDE_POINT
};


bool overlapRect(float left1, float bottom1, float right1, float top1,
                 float left2, float bottom2, float right2, float top2);

CollideResult circleCollideLine(float& collideTime, float& newCenter,
                                float center, float radius, float speed,
                                float line, bool fromAbove,
                                float timeDelta);

CollideResult circleCollideLineSegment(float& collideTime,
                       float& newCenterX, float& newCenterY,
                       float centerX, float centerY, float radius,
                       float speedX, float speedY,
                       float left, float right, float line,
                       bool fromAbove, float timeDelta);

CollideResult circleCollideTwoLines(float& collideTime,
                       float& newCenterX, float& newCenterY,
                       float& collideLine,
                       float centerX, float centerY, float radius,
                       float speedX, float speedY,
                       float left, float right, float bottom, float top,
                       float timeDelta);

bool circleCollidePoint(float& collideTime,
                        float& newCenterX, float& newCenterY,
                        float centerX, float centerY, float radius,
                        float speedX, float speedY,
                        float x, float y,
                        float timeDelta);

CollideResult circleCollideRect(float& collideTime,
                      float& newCenterX, float& newCenterY,
                      float& collideX, float& collideY,
                      float centerX, float centerY, float radius,
                      float speedX, float speedY,
                      float left, float bottom, float right, float top,
                      float timeDelta);

CollideResult rectCollideCircleHorizontal(float& newLeft,
                        float& collideX, float& collideY,
                        float left, float bottom, float right, float top,
                        float targetLeft,
                        float circleX, float circleY, float radius);

bool circleIntersectRect(float centerX, float centerY, float radius,
                         float left, float bottom, float right, float top);

} // end of namespace bump

#endif

