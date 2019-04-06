#include <gtest/gtest.h>
#include "collide.h"

using namespace bump;

bool fuzzyEq(float a, float b)
{
    const float VERY_SMALL = 1.0e-6f;
    float d = a - b;
    if(d < 0.0f) {
        d = -d;
    }
    return d < VERY_SMALL;
}

TEST(Collide, CircleCollidesRect)
{
    float left = 100.0f, bottom = 100.0f, right = 200.0f, top = 120.0f;
    float centerX = 150.0f, centerY = 140.0f, radius = 10.0f;
    float speedX = 10.0f, speedY = -10.0f;
    float timeDelta = 2.0f;
    float collideTime, newCenterX, newCenterY;


    CollideResult result = circleCollideRect(collideTime,
                                newCenterX, newCenterY,
                                centerX, centerY, radius,
                                speedX, speedY,
                                left, bottom, right, top,
                                timeDelta);

    ASSERT_EQ(result, COLLIDE_HORIZONTAL_LINE);
    ASSERT_DOUBLE_EQ(collideTime, 1.0f);
    ASSERT_DOUBLE_EQ(newCenterX, 160.0f);
    ASSERT_DOUBLE_EQ(newCenterY, 130.0f);

    centerX = 220.0f;
    centerY = 105.0f;
    speedX = -10.0f;
    speedY = 10.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_VERTICAL_LINE);
    ASSERT_DOUBLE_EQ(collideTime, 1.0f);
    ASSERT_DOUBLE_EQ(newCenterX, 210.0f);
    ASSERT_DOUBLE_EQ(newCenterY, 115.0f);

    centerX = 170.0f;
    centerY = 80.0f;
    speedX = -10.0f;
    speedY = 10.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_HORIZONTAL_LINE);
    ASSERT_DOUBLE_EQ(collideTime, 1.0f);
    ASSERT_DOUBLE_EQ(newCenterX, 160.0f);
    ASSERT_DOUBLE_EQ(newCenterY, 90.0f);

    centerX = 80.0f;
    centerY = 115.0f;
    speedX = 10.0f;
    speedY = -10.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_VERTICAL_LINE);
    ASSERT_DOUBLE_EQ(collideTime, 1.0f);
    ASSERT_DOUBLE_EQ(newCenterX, 90.0f);
    ASSERT_DOUBLE_EQ(newCenterY, 105.0f);

    centerX = 170.0f;
    centerY = 80.0f;
    speedX = -10.0f;
    speedY = 10.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_HORIZONTAL_LINE);
    ASSERT_DOUBLE_EQ(collideTime, 1.0f);
    ASSERT_DOUBLE_EQ(newCenterX, 160.0f);
    ASSERT_DOUBLE_EQ(newCenterY, 110.0f);

}
