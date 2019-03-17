#include <stdexcept>
#include "log.h"
#include "constants.h"
#include "vertexarray.h"

namespace bump {

VertexArray::VertexArray()
: m_numVertices(0)
, m_vao(0)
, m_vbo(0)
{
}

VertexArray::VertexArray(const float* vertices,
                         unsigned int numVertices)
: m_numVertices(numVertices)
, m_vao(0)
, m_vbo(0)
{
    if(!load(vertices, numVertices)) {
        throw std::runtime_error("Faield to load VertexArray");
    }
}

VertexArray::~VertexArray()
{
    destroy();
}

bool VertexArray::load(const float* vertices,
                       unsigned int numVertices)
{
    if(vertices == nullptr) {
        LOG_ERROR("vertexArray cannot be null");
        return false;
    }

    if(numVertices == 0) {
        LOG_ERROR("vertexArraySize cannot be zero");
        return false;
    }

    glGenVertexArrays(1, &m_vao);
    if(m_vao == 0) {
        LOG_ERROR("Failed to generate VAO: %d", glGetError());
        return false;
    }

    glGenBuffers(1, &m_vbo);
    if(m_vbo == 0) {
        LOG_ERROR("Failed to generate VBO: %d", glGetError());
        destroy();
        return false;
    }

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, numVertices * Constants::VERTEX_SIZE, vertices, GL_STATIC_DRAW);

    return true;
}

void VertexArray::destroy()
{
    if(m_vbo != 0) {
        glDeleteBuffers(1, &m_vbo);
        m_vbo = 0;
    }

    if(m_vao != 0) {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0;
    }
}

} // end of namespace bump
