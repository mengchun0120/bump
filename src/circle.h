#ifndef INCLUDE_CIRCLE
#define INCLUDE_CIRCLE

#include "constants.h"
#include "vertexarray.h"
#include "bumpshaderprogram.h"

namespace bump {

class Circle: public VertexArray {
public:
    Circle(GLfloat centerX, GLfloat centerY, GLfloat radius, unsigned int numVertices);

    virtual ~Circle();

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

    void draw(BumpShaderProgram& program, const GLfloat *ref,
              const GLfloat* fillColor, const GLfloat* borderColor, GLfloat borderWidth);

private:
    bool init(GLfloat centerX, GLfloat centerY, GLfloat radius, unsigned int numVertices);

protected:
    GLfloat m_centerX, m_centerY;
    GLfloat m_radius;
};

} // end of namespace bump

#endif
