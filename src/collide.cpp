#include <cmath>
#include "collide.h"

namespace bump {

bool overlapRect(float left1, float bottom1, float right1, float top1,
                 float left2, float bottom2, float right2, float top2)
{
    return left1 < right2 && right1 > left2 &&
           bottom1 < top2 && top1 > bottom2;
}

CollideResult circleCollideLine(float& collideTime, float& newCenter,
                                float center, float radius, float speed,
                                float line, bool fromAbove,
                                float timeDelta)
{
    float dist, impactTime, impactPos;

    if(fromAbove) {
        dist = center - line;
        if(dist < radius) {
            return COLLIDE_ALREADY;
        }

        if(speed >= 0.0f) {
            return COLLIDE_NOTHING;
        }

        impactTime = (dist - radius) / (-speed);
        impactPos = line + radius;

    } else {
        dist = line - center;
        if(dist < radius) {
            return COLLIDE_ALREADY;
        }

        if(speed <= 0.0f) {
            return COLLIDE_NOTHING;
        }

        impactTime = (dist - radius) / speed;
        impactPos = line - radius;
    }

    if(impactTime > timeDelta) {
        return COLLIDE_NOTHING;
    }

    collideTime = impactTime;
    newCenter = impactPos;

    return COLLIDE_INTIME;
}

CollideResult circleCollideLineSegment(float& collideTime,
                       float& newCenterX, float& newCenterY,
                       float centerX, float centerY, float radius,
                       float speedX, float speedY,
                       float left, float right, float line,
                       bool fromAbove, float timeDelta)
{
    float impactTime, impactY;
    CollideResult ret;

    ret = circleCollideLine(impactTime, impactY,
                            centerY, radius, speedY,
                            line, fromAbove,
                            timeDelta);

    if(ret == COLLIDE_ALREADY || ret == COLLIDE_NOTHING) {
        return ret;
    }

    float impactX = centerX + impactTime * speedX;

    if(impactX >= left && impactX <= right) {
        collideTime = impactTime;
        newCenterX = impactX;
        newCenterY = impactY;
        return COLLIDE_INTIME;
    }

    if(centerX >= left && centerX <= right) {
        return COLLIDE_NOTHING;
    }

    if(centerX < left) {
        if(impactX <= centerX || impactX > right) {
            return COLLIDE_NOTHING;
        }
    } else if(impactX >= centerX || impactX < left) {
        return COLLIDE_NOTHING;
    }

    return COLLIDE_POTENTIAL;
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

CollideResult circleCollideTwoLines(float& collideTime,
                            float& newCenterX, float& newCenterY,
                            float& collideLine,
                            float centerX, float centerY, float radius,
                            float speedX, float speedY,
                            float left, float right, float bottom, float top,
                            float timeDelta)
{
    if(centerY >= bottom && centerY <= top) {
        return COLLIDE_CONTAINED;
    }

    float line;
    bool fromAbove;

    if(centerY > top) {
        fromAbove = true;
        line = top;
    } else {
        fromAbove = false;
        line = bottom;
    }

    float impactTime, impactX, impactY;
    CollideResult ret;

    ret  = circleCollideLineSegment(impactTime,
                                    impactX, impactY,
                                    centerX, centerY, radius,
                                    speedX, speedY,
                                    left, right, top,
                                    true, timeDelta);

    if(ret == COLLIDE_NOTHING) {
        return COLLIDE_NOTHING;
    }

    if(ret == COLLIDE_INTIME) {
        collideTime = impactTime;
        newCenterX = impactX;
        newCenterY = impactY;
        return COLLIDE_INTIME;
    }

    collideLine = line;
    return ret;
}

CollideResult circleCollideRect(float& collideTime,
                      float& newCenterX, float& newCenterY,
                      float& collideX, float& collideY,
                      float centerX, float centerY, float radius,
                      float speedX, float speedY,
                      float left, float bottom, float right, float top,
                      float timeDelta)
{
    float horizontalLine;
    CollideResult horizontalResult;

    horizontalResult = circleCollideTwoLines(collideTime,
                                    newCenterX, newCenterY,
                                    horizontalLine,
                                    centerX, centerY, radius,
                                    speedX, speedY,
                                    left, right, bottom, top,
                                    timeDelta);

    if(horizontalResult == COLLIDE_NOTHING ||
       horizontalResult == COLLIDE_INTIME) {
        return horizontalResult;
    }

    float verticalLine;
    CollideResult verticalResult;

    verticalResult = circleCollideTwoLines(collideTime,
                                    newCenterY, newCenterX,
                                    verticalLine,
                                    centerY, centerX, radius,
                                    speedY, speedX,
                                    bottom, top, left, right,
                                    timeDelta);

    if(verticalResult == COLLIDE_NOTHING ||
       verticalResult == COLLIDE_INTIME) {
        return verticalResult;
    }

    if(horizontalResult == COLLIDE_POTENTIAL ||
       verticalResult == COLLIDE_POTENTIAL) {
        bool ret = circleCollidePoint(collideTime,
                                    newCenterX, newCenterY,
                                    centerX, centerY, radius,
                                    speedX, speedY,
                                    verticalLine, horizontalLine,
                                    timeDelta);
        if(ret) {
            collideX = verticalLine;
            collideY = horizontalLine;
            return COLLIDE_POINT;
        }
    }

    return COLLIDE_NOTHING;
}

} // end of namespace bump

