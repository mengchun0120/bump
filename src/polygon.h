#ifndef INCLUDE_POLYGON
#define INCLUDE_POLYGON

#include "constants.h"
#include "vertexarray.h"
#include "bumpshaderprogram.h"

namespace bump {

class Polygon: public VertexArray {
public:
    Polygon();

    Polygon(const GLfloat* vertices, unsigned int numVertices);

    virtual ~Polygon();

    void draw(BumpShaderProgram& program, const GLfloat* ref, const GLfloat* fillColor,
              const GLfloat* borderColor, GLfloat borderWidth);
};

} // end of namespace bump

#endif