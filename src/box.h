#ifndef INCLUDE_BOX
#define INCLUDE_BOX

#include "constants.h"
#include "rectangle.h"
#include "gameobject.h"

namespace bump {

class Box: public GameObject {
public:
    static const unsigned int TYPE_COUNT = 4;

    static float width()
    {
        return k_shape.width();
    }

    static float height()
    {
        return k_shape.height();
    }

    static void initShape();

    Box(float x, float y, int type);

    virtual ~Box();

    virtual void draw(BumpShaderProgram& program);

    bool onHit();

private:
    static Rectangle k_shape;
    static float k_colors[TYPE_COUNT][Constants::NUM_FLOATS_COLOR];
    static int k_maxLife[TYPE_COUNT];

    int m_type;
    int m_life;
    float m_color[Constants::NUM_FLOATS_COLOR];
};

} // end of namespace bump

#endif
