#ifndef INCLUDE_POLYGON
#define INCLUDE_POLYGON

#include "constants.h"
#include "vertexarray.h"
#include "bumpshaderprogram.h"

namespace bump {

class Polygon: public VertexArray {
public:
    Polygon();

    Polygon(const float *vertices, unsigned int numVertices);

    virtual ~Polygon();

    void draw(BumpShaderProgram &program, const float *ref, const float *fillColor,
              const float *borderColor, float borderWidth);
};

} // end of namespace bump

#endif
