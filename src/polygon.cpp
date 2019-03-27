#include <GL/glew.h>
#include "polygon.h"

namespace bump {

Polygon::Polygon()
: VertexArray()
{
}

Polygon::Polygon(const float *vertices, unsigned int numVertices)
: VertexArray(vertices, numVertices)
{
}

Polygon::~Polygon()
{

}

void Polygon::draw(BumpShaderProgram &program, const float *ref, const float *fillColor,
                   const float *borderColor, float borderWidth)
{
    if(ref != nullptr) {
        program.setUseObjRef(true);
        program.setObjRef(ref);
    } else {
        program.setUseObjRef(false);
    }

    program.setPosition(*this);

    if(fillColor != nullptr) {
        program.setColor(fillColor);
        glDrawArrays(GL_TRIANGLE_FAN, 0, m_numVertices);
    }

    if(borderColor != nullptr) {
        glLineWidth(borderWidth);
        program.setColor(borderColor);
        glDrawArrays(GL_LINE_LOOP, 1, m_numVertices-1);
    }
}


} // end of namespace bump
