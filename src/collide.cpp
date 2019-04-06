#include <cmath>
#include "collide.h"

namespace bump {

bool overlapRect(float left1, float bottom1, float right1, float top1,
                 float left2, float bottom2, float right2, float top2)
{
    return left1 < right2 && right1 > left2 &&
           bottom1 < top2 && top1 > bottom2;
}

bool circleCollideLine(float& collideTime, float& newCenter,
                       float center, float radius, float speed,
                       float line, bool collideFromAbove,
                       float timeDelta)
{
    float dist, impactTime, impactPos;

    if(collideFromAbove) {
        dist = center - radius - line;
        if(dist < 0 || speed > 0) {
            return false;
        }

        impactPos = line + radius;
        impactTime = dist / (-speed);

    } else {
        dist = line - center - radius;
        if(dist < 0 || speed < 0) {
            return false;
        }

        impactPos = line - radius;
        impactTime = dist / speed;
    }

    if(impactTime > timeDelta) {
        return false;
    }

    collideTime = impactTime;
    newCenter = impactPos;

    return true;
}

CollideResult circleCollideLineSegment(float& collideTime,
                       float& newCenterX, float& newCenterY,
                       float centerX, float centerY, float radius,
                       float speedX, float speedY,
                       float left, float right, float line,
                       bool collideFromAbove,
                       float timeDelta)
{
    float collideLineTime, collideY;
    bool collideLine = circleCollideLine(collideLineTime, collideY,
                                         centerY, radius, speedY,
                                         line, collideFromAbove,
                                         timeDelta);

    if(!collideLine) {
        return COLLIDE_NOTHING;
    }

    float collideX = centerX + collideLineTime * speedX;
    if(collideX < left || collideX > right) {
        return COLLIDE_LINE_ONLY;
    }

    collideTime = collideLineTime;
    newCenterX = collideX;
    newCenterY = collideY;

    return COLLIDE_TRUELY;
}

CollideResult circleCollideTwoLines(float& collideTime,
                    float& newCenterX, float& newCenterY,
                    float& collideLine,
                    float centerX, float centerY, float radius,
                    float speedX, float speedY,
                    float left, float right, float bottom, float top,
                    float timeDelta)
{
    CollideResult result;

    result = circleCollideLineSegment(collideTime,
                                      newCenterX, newCenterY,
                                      centerX, centerY, radius,
                                      speedX, speedY,
                                      left, right, top,
                                      true,
                                      timeDelta);

    if(result == COLLIDE_TRUELY || result == COLLIDE_LINE_ONLY) {
        collideLine = top;
        return result;
    }

    result = circleCollideLineSegment(collideTime,
                                      newCenterX, newCenterY,
                                      centerX, centerY, radius,
                                      speedX, speedY,
                                      left, right, bottom,
                                      false,
                                      timeDelta);

    if(result == COLLIDE_TRUELY || result == COLLIDE_LINE_ONLY) {
        collideLine = bottom;
        return result;
    }

    return COLLIDE_NOTHING;
}

bool circleCollidePoint(float& collideTime,
                        float& newCenterX, float& newCenterY,
                        float centerX, float centerY, float radius,
                        float speedX, float speedY,
                        float x, float y,
                        float timeDelta)
{
    float dx = centerX - x;
    float dy = centerY - y;
    float c = dx*dx + dy*dy - radius*radius;

    if(c < 0) {
        return false;
    }

    float b = dx*speedX + dy*speedY;

    if(b < 0) {
        return false;
    }

    float a = speedX*speedX + speedY*speedY;
    float d = b*b - a*c;

    if(d < 0) {
        return false;
    }

    float impactTime = (b - sqrt(d)) / a;

    if(impactTime > timeDelta) {
        return false;
    }

    collideTime = impactTime;
    newCenterX = centerX + speedX * collideTime;
    newCenterY = centerY + speedY * collideTime;

    return true;
}

CollideResult circleCollideRect(float& collideTime,
                      float& newCenterX, float& newCenterY,
                      float centerX, float centerY, float radius,
                      float speedX, float speedY,
                      float left, float bottom, float right, float top,
                      float timeDelta)
{
    float horizontalLine;
    CollideResult resultHorizontal;

    resultHorizontal = circleCollideTwoLines(collideTime,
                                    newCenterX, newCenterY,
                                    horizontalLine,
                                    centerX, centerY, radius,
                                    speedX, speedY,
                                    left, right, bottom, top,
                                    timeDelta);

    if(resultHorizontal == COLLIDE_TRUELY) {
        return COLLIDE_HORIZONTAL_LINE;
    }

    float verticalLine;
    CollideResult resultVertical;

    resultVertical = circleCollideTwoLines(collideTime,
                                    newCenterY, newCenterX,
                                    verticalLine,
                                    centerY, centerX, radius,
                                    speedY, speedX,
                                    bottom, top, left, right,
                                    timeDelta);

    if(resultVertical == COLLIDE_TRUELY) {
        return COLLIDE_VERTICAL_LINE;
    }

    if(resultHorizontal == COLLIDE_NOTHING ||
       resultVertical == COLLIDE_NOTHING) {
        return COLLIDE_NOTHING;
    }

    bool collidePoint;

    collidePoint = circleCollidePoint(collideTime,
                                    newCenterX, newCenterY,
                                    centerX, centerY, radius,
                                    speedX, speedY,
                                    verticalLine, horizontalLine,
                                    timeDelta);

    if(collidePoint) {
        return COLLIDE_POINT;
    }

    return COLLIDE_NOTHING;
}

} // end of namespace bump

