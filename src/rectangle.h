#ifndef INCLUDE_RECTANGLE
#define INCLUDE_RECTANGLE

#include "bumpshaderprogram.h"

namespace bump {

class Rectangle: public VertexArray {
public:
    Rectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height);

    virtual ~Rectangle();

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

    void draw(BumpShaderProgram& program, const GLfloat *ref,
              const GLfloat* fillColor, const GLfloat* borderColor, GLfloat borderWidth);

protected:
    GLfloat m_x;
    GLfloat m_y;
    GLfloat m_width;
    GLfloat m_height;
};

} // end of namespace bump

#endif

