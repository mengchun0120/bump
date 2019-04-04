#ifndef INCLUDE_COLLIDE
#define INCLUDE_COLLIDE

namespace bump {

enum CollideResult {
    COLLIDE_LINE_ONLY,
    COLLIDE_TRUELY,
    COLLIDE_HORIZONTAL_LINE,
    COLLIDE_VERTICAL_LINE,
    COLLIDE_POINT,
    COLLIDE_NOTHING
};

bool overlapRect(float left1, float bottom1, float right1, float top1,
                 float left2, float bottom2, float right2, float top2);

bool circleCollideLine(float& collideTime, float& newCenter,
                       float center, float radius, float speed,
                       float line, bool collideFromAbove,
                       float timeDelta);

CollideResult circleCollideLineSegment(float& collideTime,
                       float& newCenterX, float& newCenterY,
                       float centerX, float centerY, float radius,
                       float speedX, float speedY,
                       float left, float right, float line,
                       bool collideFromAbove,
                       float timeDelta);

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
                      float centerX, float centerY, float radius,
                      float speedX, float speedY,
                      float left, float bottom, float right, float top,
                      float timeDelta);

} // end of namespace bump

#endif

