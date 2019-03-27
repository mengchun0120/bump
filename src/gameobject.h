#ifndef INCLUDE_GAMEOBJECT
#define INCLUDE_GAMEOBJECT

#include "bumpshaderprogram.h"
#include "constants.h"

namespace bump {

class GameObject {
public:
    GameObject();

    GameObject(float x, float y);

    virtual ~GameObject();

    virtual void draw(BumpShaderProgram& program) = 0;

    float& x()
    {
        return m_pos[0];
    }

    float& y()
    {
        return m_pos[1];
    }

protected:
    float m_pos[Constants::NUM_FLOATS_PER_VERTEX];
};

} // end of namespace bump

#endif

