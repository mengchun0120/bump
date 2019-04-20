#ifndef INCLUDE_BAT
#define INCLUDE_BAT

#include "gameobject.h"
#include "rectangle.h"

namespace bump {

class Game;

class Bat: public GameObject {
public:
    Bat(Game& game);

    virtual ~Bat();

    virtual void draw(BumpShaderProgram& program);

    void move(float newX);

    float width() const
    {
        return m_shape.width();
    }

    float height() const
    {
        return m_shape.height();
    }

    float right() const
    {
        return x() + m_shape.width();
    }

    float top() const
    {
        return y() + m_shape.height();
    }

protected:
    Game& m_game;
    float m_xBound;
    Rectangle m_shape;
    float m_fillColor[Constants::NUM_FLOATS_COLOR];
};

} // end of namespace bump

#endif

