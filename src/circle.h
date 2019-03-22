#ifndef INCLUDE_CIRCLE
#define INCLUDE_CIRCLE

#include "polygon.h"

namespace bump {

class Circle: public Polygon {
public:
    Circle();

    Circle(GLfloat centerX, GLfloat centerY, GLfloat radius, unsigned int numVertices);

    virtual ~Circle();

    bool init(GLfloat centerX, GLfloat centerY, GLfloat radius, unsigned int numVertices);

    GLfloat centerX() const
    {
        return m_centerX;
    }

    GLfloat centerY() const
    {
        return m_centerY;
    }

    GLfloat radius() const
    {
        return m_radius;
    }

protected:
    GLfloat m_centerX, m_centerY;
    GLfloat m_radius;
};

} // end of namespace bump

#endif
