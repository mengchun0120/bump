#ifndef INCLUDE_RECTANGLE
#define INCLUDE_RECTANGLE

#include "polygon.h"

namespace bump {

class Rectangle: public Polygon {
public:
    Rectangle();

    Rectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height);

    virtual ~Rectangle();

    bool init(GLfloat x, GLfloat y, GLfloat width, GLfloat height);

    GLfloat x() const
    {
        return m_x;
    }

    GLfloat y() const
    {
        return m_y;
    }

    GLfloat width() const
    {
        return m_width;
    }

    GLfloat height() const
    {
        return m_height;
    }

protected:
    GLfloat m_x;
    GLfloat m_y;
    GLfloat m_width;
    GLfloat m_height;
};

} // end of namespace bump

#endif

