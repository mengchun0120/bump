#ifndef INCLUDE_BAT
#define INCLUDE_BAT

#include "gameobject.h"
#include "rectangle.h"

namespace bump {

class Bat: public GameObject {
public:
    Bat(float gameWidth, float gameHeight);

    virtual ~Bat();

    virtual void draw(BumpShaderProgram& program);

    void move(float newX);

protected:
    float m_xBound;
    Rectangle m_shape;
    float m_fillColor[Constants::NUM_FLOATS_COLOR];
};

} // end of namespace bump

#endif

