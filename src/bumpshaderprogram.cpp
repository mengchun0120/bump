#include <GL/glew.h>
#include "config.h"
#include "log.h"
#include "constants.h"
#include "bumpshaderprogram.h"

namespace bump {

BumpShaderProgram::BumpShaderProgram(const std::string& vertexShaderFile, const std::string& fragShaderFile)
: ShaderProgram(vertexShaderFile, fragShaderFile)
{
    loadParam();
}

BumpShaderProgram::~BumpShaderProgram()
{
}

void BumpShaderProgram::loadParam()
{
    m_positionLocation = glGetAttribLocation(m_program, "position");
    m_useObjRefLocation = glGetUniformLocation(m_program, "useObjRef");
    m_objRefLocation = glGetUniformLocation(m_program, "objRef");
    m_viewportSizeLocation = glGetUniformLocation(m_program, "viewportSize");
    m_viewportOriginLocation = glGetUniformLocation(m_program, "viewportOrigin");
    m_colorLocation = glGetUniformLocation(m_program, "color");
}

void BumpShaderProgram::setUseObjRef(bool enabled)
{
    glUniform1i(m_useObjRefLocation, enabled ? 1 : 0);
}

void BumpShaderProgram::setObjRef(const float* objRef)
{
    glUniform2fv(m_objRefLocation, 1, objRef);
}

void BumpShaderProgram::setViewportSize(const float* viewportSize)
{
    glUniform2fv(m_viewportSizeLocation, 1, viewportSize);
}

void BumpShaderProgram::setViewportOrigin(const float* viewportOrigin)
{
    glUniform2fv(m_viewportOriginLocation, 1, viewportOrigin);
}

void BumpShaderProgram::setColor(const float* color)
{
    glUniform4fv(m_colorLocation, 1, color);
}

void BumpShaderProgram::setPosition(const VertexArray& vertexArray)
{
    glBindVertexArray(vertexArray.vao());

    glBindBuffer(GL_ARRAY_BUFFER, vertexArray.vbo());
    if(vertexArray.ebo() != 0) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArray.ebo());
    }

    glVertexAttribPointer(m_positionLocation, Constants::NUM_FLOATS_PER_VERTEX, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(m_positionLocation);
}

} // end of namespace bump
