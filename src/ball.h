#ifndef INCLUDE_BALL
#define INCLUDE_BALL

#include "gameobject.h"
#include "circle.h"
#include "constants.h"

namespace bump {

class Game;

class Ball: public GameObject {
public:
    Ball(Game& game);

    virtual ~Ball();

    void init(float x, float y, float speedX, float speedY);

    float radius() const
    {
        return m_shape.radius();
    }

    virtual void draw(BumpShaderProgram& program);

    bool update(float timeDelta);

protected:
    Game& m_game;
    Circle m_shape;
    float m_speedX, m_speedY;
    float m_color[Constants::NUM_FLOATS_COLOR];
};

} // end of namespace bump

#endif

