#ifndef INCLUDE_VERTEXARRAY
#define INCLUDE_VERTEXARRAY

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
    unsigned int m_numIndices;
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;
};

} // end of namespace bump

#endif
