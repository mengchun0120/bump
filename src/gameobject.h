#ifndef INCLUDE_GAMEOBJECT
#define INCLUDE_GAMEOBJECT

#include "bumpshaderprogram.h"
#include "constants.h"

namespace bump {

class GameObject {
public:
    GameObject();

    GameObject(GLfloat x, GLfloat y);

    virtual ~GameObject();

    virtual void draw(BumpShaderProgram& program) = 0;

    GLfloat& x()
    {
        return m_pos[0];
    }

    GLfloat& y()
    {
        return m_pos[1];
    }

protected:
    GLfloat m_pos[Constants::NUM_FLOATS_PER_VERTEX];
};

} // end of namespace bump

#endif

