#ifndef INCLUDE_BALL
#define INCLUDE_BALL

#include "gameobject.h"
#include "circle.h"
#include "constants.h"

namespace bump {

class Game;

class Ball: public GameObject {
public:
    struct CollideImpact {
        float m_collideTime;
        float m_newCenterX, m_newCenterY;
        float m_newSpeedX, m_newSpeedY;

        CollideImpact& operator=(const CollideImpact& other)
        {
            m_collideTime = other.m_collideTime;
            m_newCenterX = other.m_newCenterX;
            m_newCenterY = other.m_newCenterY;
            m_newSpeedX = other.m_newSpeedX;
            m_newSpeedY = other.m_newSpeedY;
            return *this;
        }
    };

public:
    Ball(Game& game);

    virtual ~Ball();

    void init(float x, float y, float speed);

    float radius() const
    {
        return m_shape.radius();
    }

    virtual void draw(BumpShaderProgram& program);

    bool update(float timeDelta);

private:
    bool collideBoundary(CollideImpact& impact, float timeDelta);

    bool collideRect(CollideImpact& impact,
                     float left, float bottom, float right, float top,
                     float timeDelta);

protected:
    Game& m_game;
    Circle m_shape;
    float m_speed;
    float m_speedX, m_speedY;
    float m_color[Constants::NUM_FLOATS_COLOR];
};

} // end of namespace bump

#endif

