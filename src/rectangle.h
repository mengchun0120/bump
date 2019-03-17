#ifndef INCLUDE_RECTANGLE
#define INCLUDE_RECTANGLE

#include "bumpshaderprogram.h"

namespace bump {

class Rectangle: public VertexArray {
public:
    Rectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height);

    virtual ~Rectangle();

    void draw(BumpShaderProgram& program, const GLfloat *ref, const GLfloat *color);
};

} // end of namespace bump

#endif

