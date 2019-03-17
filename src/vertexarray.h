#ifndef INCLUDE_VERTEXARRAY
#define INCLUDE_VERTEXARRAY

#include <GL/glew.h>

namespace bump {

class VertexArray {
public:
    VertexArray();

    VertexArray(const float* vertices,
                unsigned int numVertices);

    virtual ~VertexArray();

    bool load(const float* vertices,
              unsigned int numVertices);

    unsigned int numVertices() const
    {
        return m_numVertices;
    }

    GLuint vao() const
    {
        return m_vao;
    }

    GLuint vbo() const
    {
        return m_vbo;
    }

protected:
    void destroy();

    unsigned int m_numVertices;
    GLuint m_vao;
    GLuint m_vbo;
};

} // end of namespace bump

#endif
