#include "collide.h"

namespace bump {

enum CollideResult {
    COLLIDE_LINE_ONLY,
    COLLIDE_TRUELY,
    COLLIDE_NOTHING
};

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
        impactTime = dist / speed;

    } else {
        dist = line - center - radius;
        if(dist < 0 || speed < 0) {
            return false;
        }

        impactPos = line - radius;
        impactTime = dist / (-speed);
    }

    if(impactTime > timeDelta) {
        return false;
    }

    collideTime = impactTime;
    newCenter = impactPos;

    return true;
}

bool circleCollideLineSegment(float& collideTime,
                              float& newCenterX, float& newCenterY,
                              float centerX, float centerY, float radius,
                              float speedX, float speedY,
                              float left, float right, float line,
                              bool collideFromAbove)
{
    float collideLineTime, collideY;
    bool collideLine = circleCollideLine(collideLineTime, collideY,
                                         centerY, radius,
                                         speedY, line, collideFromAbove);

    if(!collideLine) {
        return false;
    }

    float 
}

CollideResult circleCollideTwoLines(float& collideTime, float& newS, float& newT, float& collideLine,
                                    float centerS, float centerT, float radius,
                                    float speedS, float speedT, float s1, float s2,
                                    float t1, float t2, float timeDelta)
{
    float time, collideT;

    if(centerT - radius >= t2 && speedT < 0) {
        time = (centerT - radius - t2) / (-speedT);
        if(time > timeDelta) {
            return COLLIDE_NOTHING;
        }

        collideLine = t2;
        collideT = t2 + radius;

    } else if(centerT + radius <= t1 && speedT > 0) {
        time = (t1 - centerT - radius) / speedT;
        if(time > timeDelta) {
            return COLLIDE_NOTHING;
        }

        collideLine = t1;
        collideT = t1 - radius;

    } else {
        return COLLIDE_NOTHING;
    }

    float collideS = centerS + speedS * time;
    if(collideS >= s1 && collideS <= s2) {
        collideTime = time;
        newS = collideS;
        newT = collideT;
        return COLLIDE_TRUELY;
    }

    return COLLIDE_LINE_ONLY;
}

bool overlapRect(float left1, float bottom1, float right1, float top1,
                 float left2, float bottom2, float right2, float top2)
{
    return left1 < right2 && right1 > left2 && bottom1 < top2 && top1 > bottom2;
}

bool circleCollidePoint(float& collideTime, float centerX, float centerY,
                        float radius, float speedX, float speedY,
                        float x, float y)
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

    collideTime = (b - sqrt(d)) / a;
    return true;
}

bool circleCollideRect(float& collideTime, float& newCenterX, float& newCenterY,
                       float& newSpeedX, float& newSpeedY, float centerX,
                       float centerY, float radius, float speedX, float speedY,
                       float left, float bottom, float right, float top, float timeDelta)
{
    float collideHorizontalLine;
    CollideResult collideResultHorizontal
                    = circleCollideTwoLines(collideTime,
                                    newCenterX, newCenterY,
                                    collideHorizontalLine,
                                    centerX, centerY, radius,
                                    speedX, speedY,
                                    left, right,
                                    bottom, top,
                                    timeDelta);

    if(collideResultHorizontal == COLLIDE_TRUELY) {
        newSpeedX = speedX;
        newSpeedY = -speedY;
        return true;
    }

    float collideVerticalLine;
    CollideResult collideResultVertical
                    = circleCollideTwoLines(collideTime,
                                    newCenterY, newCenterX,
                                    collideVerticalLine,
                                    centerY, centerX, radius,
                                    speedY, speedX,
                                    bottom, top,
                                    left, right,
                                    timeDelta);

    if(collideResultVertical == COLLIDE_TRUELY) {
        newSpeedX = -speedX;
        newSpeedY = speedY;
        return true;
    }

    if(collideResultHorizontal == COLLIDE_NOTHING ||
       collideResultVertical == COLLIDE_NOTHING) {
        return false;
    }

    float collidePointTime;
    bool collidePoint = circleCollidePoint(collidePointTime,
                                    centerX, centerY, radius,
                                    speedX, speedY,
                                    collideHorizontalLine,
                                    collideVerticalLine);

    if(collidePoint && collidePointTime < timeDelta) {
        
    }
    

    return false;
}


} // end of namespace bump

