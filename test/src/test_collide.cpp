#include <gtest/gtest.h>
#include "collide.h"

using namespace bump;

TEST(CircleCollideRect, CollideCase1)
{
    float left = 100.0f, bottom = 100.0f, right = 200.0f, top = 120.0f;
    float centerX = 150.0f, centerY = 140.0f, radius = 10.0f;
    float speedX = 10.0f, speedY = -10.0f;
    float timeDelta = 2.0f;
    float collideTime, newCenterX, newCenterY;
    float collideX, collideY;

    CollideResult result = circleCollideRect(collideTime,
                                newCenterX, newCenterY,
                                collideX, collideY,
                                centerX, centerY, radius,
                                speedX, speedY,
                                left, bottom, right, top,
                                timeDelta);

    ASSERT_EQ(result, COLLIDE_HORIZONTAL);
    ASSERT_DOUBLE_EQ(collideTime, 1.0f);
    ASSERT_DOUBLE_EQ(newCenterX, 160.0f);
    ASSERT_DOUBLE_EQ(newCenterY, 130.0f);

    centerX = 220.0f;
    centerY = 105.0f;
    speedX = -10.0f;
    speedY = 10.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            collideX, collideY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_VERTICAL);
    ASSERT_DOUBLE_EQ(collideTime, 1.0f);
    ASSERT_DOUBLE_EQ(newCenterX, 210.0f);
    ASSERT_DOUBLE_EQ(newCenterY, 115.0f);

    centerX = 170.0f;
    centerY = 80.0f;
    speedX = -10.0f;
    speedY = 10.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            collideX, collideY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_HORIZONTAL);
    ASSERT_DOUBLE_EQ(collideTime, 1.0f);
    ASSERT_DOUBLE_EQ(newCenterX, 160.0f);
    ASSERT_DOUBLE_EQ(newCenterY, 90.0f);

    centerX = 80.0f;
    centerY = 115.0f;
    speedX = 10.0f;
    speedY = -10.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            collideX, collideY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_VERTICAL);
    ASSERT_DOUBLE_EQ(collideTime, 1.0f);
    ASSERT_DOUBLE_EQ(newCenterX, 90.0f);
    ASSERT_DOUBLE_EQ(newCenterY, 105.0f);

}

TEST(CircleCollideRect, CollideCase2)
{
    float left = 100.0f, bottom = 100.0f, right = 200.0f, top = 120.0f;
    float centerX, centerY, radius = 10.0f;
    float speedX, speedY;
    float timeDelta = 2.0f;
    float collideTime, newCenterX, newCenterY;
    float collideX, collideY;
    CollideResult result;

    centerX = 215.0f;
    centerY = 140.0f;
    speedX = -20.0f;
    speedY = -10.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            collideX, collideY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_HORIZONTAL);
    ASSERT_DOUBLE_EQ(collideTime, 1.0f);
    ASSERT_DOUBLE_EQ(newCenterX, 195.0f);
    ASSERT_DOUBLE_EQ(newCenterY, 130.0f);

    centerX = 220.0f;
    centerY = 135.0f;
    speedX = -10.0f;
    speedY = -20.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            collideX, collideY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_VERTICAL);
    ASSERT_DOUBLE_EQ(collideTime, 1.0f);
    ASSERT_DOUBLE_EQ(newCenterX, 210.0f);
    ASSERT_DOUBLE_EQ(newCenterY, 115.0f);

    centerX = 85.0f;
    centerY = 140.0f;
    speedX = 20.0f;
    speedY = -10.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            collideX, collideY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_HORIZONTAL);
    ASSERT_DOUBLE_EQ(collideTime, 1.0f);
    ASSERT_DOUBLE_EQ(newCenterX, 105.0f);
    ASSERT_DOUBLE_EQ(newCenterY, 130.0f);

    centerX = 80.0f;
    centerY = 135.0f;
    speedX = 10.0f;
    speedY = -20.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            collideX, collideY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_VERTICAL);
    ASSERT_DOUBLE_EQ(collideTime, 1.0f);
    ASSERT_DOUBLE_EQ(newCenterX, 90.0f);
    ASSERT_DOUBLE_EQ(newCenterY, 115.0f);

    centerX = 85.0f;
    centerY = 80.0f;
    speedX = 20.0f;
    speedY = 10.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            collideX, collideY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_HORIZONTAL);
    ASSERT_DOUBLE_EQ(collideTime, 1.0f);
    ASSERT_DOUBLE_EQ(newCenterX, 105.0f);
    ASSERT_DOUBLE_EQ(newCenterY, 90.0f);

    centerX = 80.0f;
    centerY = 85.0f;
    speedX = 10.0f;
    speedY = 20.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            collideX, collideY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_VERTICAL);
    ASSERT_DOUBLE_EQ(collideTime, 1.0f);
    ASSERT_DOUBLE_EQ(newCenterX, 90.0f);
    ASSERT_DOUBLE_EQ(newCenterY, 105.0f);
}

TEST(CircleCollideRect, CollideCase3)
{
    float left = 100.0f, bottom = 100.0f, right = 200.0f, top = 120.0f;
    float centerX, centerY, radius = 10.0f;
    float speedX, speedY;
    float timeDelta = 2.0f;
    float collideTime, newCenterX, newCenterY;
    float collideX, collideY;
    CollideResult result;

    centerX = 95.0f;
    centerY = 140.0f;
    speedX = 10.0f;
    speedY = -10.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            collideX, collideY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_HORIZONTAL);
    ASSERT_DOUBLE_EQ(collideTime, 1.0f);
    ASSERT_DOUBLE_EQ(newCenterX, 105.0f);
    ASSERT_DOUBLE_EQ(newCenterY, 130.0f);

    centerX = 220.0f;
    centerY = 95.0f;
    speedX = -10.0f;
    speedY = 10.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            collideX, collideY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_VERTICAL);
    ASSERT_DOUBLE_EQ(collideTime, 1.0f);
    ASSERT_DOUBLE_EQ(newCenterX, 210.0f);
    ASSERT_DOUBLE_EQ(newCenterY, 105.0f);
}

TEST(CircleCollideRect, CollideCase4)
{
    float left = 100.0f, bottom = 100.0f, right = 200.0f, top = 120.0f;
    float centerX, centerY, radius = 5.0f;
    float speedX, speedY;
    float timeDelta = 2.0f;
    float collideTime, newCenterX, newCenterY;
    float collideX, collideY;
    CollideResult result;

    centerX = 213.0f;
    centerY = 134.0f;
    speedX = -10.0f;
    speedY = -10.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            collideX, collideY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_POINT);
    ASSERT_DOUBLE_EQ(collideTime, 1.0f);
    ASSERT_DOUBLE_EQ(newCenterX, 203.0f);
    ASSERT_DOUBLE_EQ(newCenterY, 124.0f);
    ASSERT_DOUBLE_EQ(collideX, 200.0f);
    ASSERT_DOUBLE_EQ(collideY, 120.0f);

    centerX = 87.0f;
    centerY = 86.0f;
    speedX = 10.0f;
    speedY = 10.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            collideX, collideY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_POINT);
    ASSERT_DOUBLE_EQ(collideTime, 1.0f);
    ASSERT_DOUBLE_EQ(newCenterX, 97.0f);
    ASSERT_DOUBLE_EQ(newCenterY, 96.0f);
    ASSERT_DOUBLE_EQ(collideX, 100.0f);
    ASSERT_DOUBLE_EQ(collideY, 100.0f);
}

TEST(CircleCollideRect, NotCollideCase1)
{
    float left = 100.0f, bottom = 100.0f, right = 200.0f, top = 120.0f;
    float centerX, centerY, radius = 10.0f;
    float speedX, speedY;
    float timeDelta = 2.0f;
    float collideTime, newCenterX, newCenterY;
    float collideX, collideY;
    CollideResult result;

    centerX = 175.0f;
    centerY = 135.0f;
    speedX = 10.0f;
    speedY = 10.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            collideX, collideY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_NOTHING);

    centerX = 135.0f;
    centerY = 160.0f;
    speedX = 10.0f;
    speedY = 10.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            collideX, collideY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_NOTHING);

    centerX = 85.0f;
    centerY = 115.0f;
    speedX = -10.0f;
    speedY = 10.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            collideX, collideY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_NOTHING);

    centerX = 40.0f;
    centerY = 115.0f;
    speedX = 10.0f;
    speedY = 10.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            collideX, collideY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_NOTHING);
}

TEST(CircleCollideRect, NotCollideCase2)
{
    float left = 100.0f, bottom = 100.0f, right = 200.0f, top = 120.0f;
    float centerX, centerY, radius = 10.0f;
    float speedX, speedY;
    float timeDelta = 2.0f;
    float collideTime, newCenterX, newCenterY;
    float collideX, collideY;
    CollideResult result;

    centerX = 215.0f;
    centerY = 85.0f;
    speedX = 10.0f;
    speedY = 0.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            collideX, collideY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_NOTHING);

    centerX = 67.0f;
    centerY = 66.0f;
    speedX = 10.0f;
    speedY = 10.0f;
    radius = 5.0f;

    result = circleCollideRect(collideTime,
                            newCenterX, newCenterY,
                            collideX, collideY,
                            centerX, centerY, radius,
                            speedX, speedY,
                            left, bottom, right, top,
                            timeDelta);

    ASSERT_EQ(result, COLLIDE_NOTHING);
}

TEST(RectCollideCircle, CollideCase)
{
    float left = 100.0f, bottom = 100.0f, right = 200.0f, top = 120.0f;
    float targetLeft, circleX, circleY, radius = 5.0f;
    float newLeft, collideX, collideY;
    CollideResult result;

    circleX = 213.0f;
    circleY = 124.0f;
    targetLeft = 115.0f;

    result = rectCollideCircleHorizontal(newLeft, collideX, collideY,
                                         left, bottom, right, top,
                                         targetLeft,
                                         circleX, circleY, radius);

    ASSERT_EQ(result, COLLIDE_POINT);
    ASSERT_DOUBLE_EQ(newLeft, 110.0f);
    ASSERT_DOUBLE_EQ(collideX, 210.0f);
    ASSERT_DOUBLE_EQ(collideY, 120.0f);

    circleX = 91.0f;
    circleY = 97.0f;
    targetLeft = 90.0f;

    result = rectCollideCircleHorizontal(newLeft, collideX, collideY,
                                         left, bottom, right, top,
                                         targetLeft,
                                         circleX, circleY, radius);

    ASSERT_EQ(result, COLLIDE_POINT);
    ASSERT_DOUBLE_EQ(newLeft, 95.0f);
    ASSERT_DOUBLE_EQ(collideX, 95.0f);
    ASSERT_DOUBLE_EQ(collideY, 100.0f);

    circleX = 210.0f;
    circleY = 115.0f;
    targetLeft = 115.0f;

    result = rectCollideCircleHorizontal(newLeft, collideX, collideY,
                                         left, bottom, right, top,
                                         targetLeft,
                                         circleX, circleY, radius);

    ASSERT_EQ(result, COLLIDE_VERTICAL);
    ASSERT_EQ(newLeft, 105.0f);

    circleX = 90.0f;
    circleY = 95.0f;
    targetLeft = 80.0f;

    result = rectCollideCircleHorizontal(newLeft, collideX, collideY,
                                         left, bottom, right, top,
                                         targetLeft,
                                         circleX, circleY, radius);

    ASSERT_EQ(result, COLLIDE_HORIZONTAL);
    ASSERT_EQ(newLeft, 80.0f);
}

TEST(RectCollideCircle, NotCollideCase)
{
    float left = 100.0f, bottom = 100.0f, right = 200.0f, top = 120.0f;
    float targetLeft, circleX, circleY, radius = 5.0f;
    float newLeft, collideX, collideY;
    CollideResult result;

    circleX = 150.0f;
    circleY = 130.0f;
    targetLeft = 115.0f;

    result = rectCollideCircleHorizontal(newLeft, collideX, collideY,
                                         left, bottom, right, top,
                                         targetLeft,
                                         circleX, circleY, radius);

    ASSERT_EQ(result, COLLIDE_NOTHING);

    circleX = 250.0f;
    circleY = 115.0f;
    targetLeft = 120.0f;

    result = rectCollideCircleHorizontal(newLeft, collideX, collideY,
                                         left, bottom, right, top,
                                         targetLeft,
                                         circleX, circleY, radius);

    ASSERT_EQ(result, COLLIDE_NOTHING);
}
