#ifndef INCLUDE_BAT
#define INCLUDE_BAT

#include "gameobject.h"
#include "rectangle.h"

namespace bump {

class Bat: public GameObject {
public:
    Bat(GLfloat gameWidth, GLfloat gameHeight);

    virtual ~Bat();

    virtual void draw(BumpShaderProgram& program);

    void move(GLfloat newX);

protected:
    GLfloat m_xBound;
    Rectangle m_shape;
    GLfloat m_fillColor[Constants::NUM_FLOATS_COLOR];
};

} // end of namespace bump

#endif

