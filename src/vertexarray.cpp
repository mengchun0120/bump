#include <stdexcept>
#include "log.h"
#include "constants.h"
#include "vertexarray.h"

namespace bump {

VertexArray::VertexArray()
: m_numVertices(0)
, m_numIndices(0)
, m_vao(0)
, m_vbo(0)
, m_ebo(0)
{
}

VertexArray::VertexArray(const float* vertices,
                         unsigned int numVertices,
                         const unsigned short* indices,
                         unsigned int numIndices)
: VertexArray()
{
    if(!load(vertices, numVertices, indices, numIndices)) {
        throw std::runtime_error("Faield to load VertexArray");
    }
}

VertexArray::~VertexArray()
{
    destroy();
}

bool VertexArray::load(const float* vertices,
                       unsigned int numVertices,
                       const unsigned short* indices,
                       unsigned int numIndices)
{
    if(vertices == nullptr) {
        LOG_ERROR("vertexArray cannot be null");
        return false;
    }

    if(numVertices == 0) {
        LOG_ERROR("vertexArraySize cannot be zero");
        return false;
    }

    if(indices != nullptr && numIndices == 0) {
        LOG_ERROR("numIndices cannot be zero");
        return false;
    }

    glGenVertexArrays(1, &m_vao);
    if(m_vao == 0) {
        LOG_ERROR("Failed to generate VAO: %d", glGetError());
        return false;
    }

    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    if(m_vbo == 0) {
        LOG_ERROR("Failed to generate VBO: %d", glGetError());
        return false;
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, numVertices * Constants::VERTEX_SIZE, vertices, GL_STATIC_DRAW);

    if(indices != nullptr) {
        glGenBuffers(1, &m_ebo);
        if(m_ebo == 0) {
            LOG_ERROR("Failed to generate EBO: %d", glGetError());
            return false;
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned short), indices, GL_STATIC_DRAW);
    }

    return true;
}

void VertexArray::destroy()
{
    if(m_ebo != 0) {
        glDeleteBuffers(1, &m_ebo);
    }

    if(m_vbo != 0) {
        glDeleteBuffers(1, &m_vbo);
    }

    if(m_vao != 0) {
        glDeleteVertexArrays(1, &m_vao);
    }
}

} // end of namespace bump
