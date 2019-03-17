#ifndef INCLUDE_VERTEXARRAY
#define INCLUDE_VERTEXARRAY

#include <GL/glew.h>

namespace bump {

class VertexArray {
public:
    VertexArray();

    VertexArray(const float* vertices,
                unsigned int numVertices,
                const unsigned short* indices=nullptr,
                unsigned int numIndices=0);

    virtual ~VertexArray();

    bool load(const float* vertices,
              unsigned int numVertices,
              const unsigned short* indices=nullptr,
              unsigned int numIndices=0);

    unsigned int numVertices() const
    {
        return m_numVertices;
    }

    unsigned int numIndices() const
    {
        return m_numIndices;
    }

    GLuint vao() const
    {
        return m_vao;
    }

    GLuint vbo() const
    {
        return m_vbo;
    }

    GLuint ebo() const
    {
        return m_ebo;
    }

protected:
    void destroy();

    unsigned int m_numVertices;
    unsigned int m_numIndices;
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
};

} // end of namespace bump

#endif
