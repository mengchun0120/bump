#ifndef INCLUDE_VERTEXARRAY
#define INCLUDE_VERTEXARRAY

#include "constants.h"

namespace bump {

class VertexArray {
public:
    static bool loadRectVertexArray(VertexArray& va, float width, float height);

    VertexArray();

    VertexArray(const float* vertices,
                unsigned int numVertices0,
                bool hasTexCoord0,
                const unsigned short* indices=nullptr,
                unsigned int numIndices0=0);

    virtual ~VertexArray();

    bool load(const float* vertices,
              unsigned int numVertices0,
              bool hasTexCoord0,
              const unsigned short* indices=nullptr,
              unsigned int numIndices0=0);

    unsigned int numVertices() const
    {
        return m_numVertices;
    }

    bool hasTexCoord() const
    {
        return m_hasTexCoord;
    }

    unsigned int vertexSize() const
    {
        return m_vertexSize;
    }

    unsigned int stride() const
    {
        return m_stride;
    }

    unsigned int numIndices() const
    {
        return m_numIndices;
    }

    unsigned int vao() const
    {
        return m_vao;
    }

    unsigned int vbo() const
    {
        return m_vbo;
    }

    unsigned int ebo() const
    {
        return m_ebo;
    }

protected:
    void destroy();

    unsigned int m_numVertices;
    bool m_hasTexCoord;
    unsigned int m_vertexSize;
    unsigned int m_stride;
    unsigned int m_numIndices;
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;
};

} // end of namespace bump

#endif
