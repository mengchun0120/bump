#ifndef INCLUDE_BALL
#define INCLUDE_BALL

#include "gameobject.h"
#include "circle.h"
#include "constants.h"

class BumpShaderProgram;
class Game;

namespace bump {

class Ball: public GameObject {
public:
    Ball();

    virtual ~Ball();

    void init(float x, float y, float speedX, float speedY);

    virtual void draw(BumpShaderProgram& program);

    float radius() const
    {
        return m_shape.radius();
    }

    void update(Game& game, float timeDelta);

protected:
    Circle m_shape;
    float m_speedX, m_speedY;
    float m_color[Constants::NUM_FLOATS_COLOR];
};

} // end of namespace bump

#endif

