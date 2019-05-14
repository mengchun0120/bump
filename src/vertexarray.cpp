#include <stdexcept>
#include <GL/glew.h>
#include "log.h"
#include "constants.h"
#include "vertexarray.h"

namespace bump {

bool VertexArray::loadRectVertexArray(VertexArray& va, float width, float height)
{
    float vertices[] = {
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, height, 0.0f, 1.0f,
        width, height, 1.0f, 1.0f,
        width, 0.0f, 1.0f, 0.0f
    };

    unsigned short indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    return va.load(vertices, 4, true, indices, 6);
}

VertexArray::VertexArray()
: m_numVertices(0)
, m_hasTexCoord(false)
, m_vertexSize(0)
, m_stride(0)
, m_numIndices(0)
, m_vao(0)
, m_vbo(0)
, m_ebo(0)
{
}

VertexArray::VertexArray(const float* vertices,
                         unsigned int numVertices0,
                         bool hasTexCoord0,
                         const unsigned short* indices,
                         unsigned int numIndices0)
: VertexArray()
{
    if(!load(vertices, numVertices0, hasTexCoord0, indices, numIndices0)) {
        throw std::runtime_error("Faield to load VertexArray");
    }
}

VertexArray::~VertexArray()
{
    destroy();
}

bool VertexArray::load(const float* vertices,
                       unsigned int numVertices0,
                       bool hasTexCoord0,
                       const unsigned short* indices,
                       unsigned int numIndices0)
{
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

    m_vertexSize = Constants::POSITION_SIZE;
    if(hasTexCoord0) {
        m_vertexSize += Constants::TEXCOORD_SIZE;
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 numVertices0 * m_vertexSize,
                 vertices,
                 GL_STATIC_DRAW);

    m_numVertices = numVertices0;
    m_hasTexCoord = hasTexCoord0;
    m_stride = m_hasTexCoord ? m_vertexSize : 0;

    if(indices != nullptr) {
        glGenBuffers(1, &m_ebo);
        if(m_ebo == 0) {
            LOG_ERROR("Failed to generate EBO: %d", glGetError());
            return false;
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     numIndices0 * sizeof(unsigned short),
                     indices,
                     GL_STATIC_DRAW);
        m_numIndices = numIndices0;
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

