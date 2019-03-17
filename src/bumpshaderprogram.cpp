#include <stdexcept>
#include "config.h"
#include "log.h"
#include "bumpshaderprogram.h"

namespace bump {

BumpShaderProgram::BumpShaderProgram(const std::string& vertexShaderFile, const std::string& fragShaderFile)
: ShaderProgram(vertexShaderFile, fragShaderFile)
{
    if(!loadParam()) {
        throw std::runtime_error("Failed to load param");
    }
}

BumpShaderProgram::~BumpShaderProgram()
{
}

bool BumpShaderProgram::loadParam()
{
    GLenum err;

    m_posLocation = glGetAttribLocation(m_program, "pos");
    err = glGetError();
    if(GL_NO_ERROR != err) {
        LOG_ERROR("Failed to get attribute location for pos: %d", static_cast<int>(err));
        return false;
    }

    m_colorLocation = glGetUniformLocation(m_program, "color");
    if(GL_NO_ERROR != err) {
        LOG_ERROR("Failed to get uniform location for color: %d", static_cast<int>(err));
        return false;
    }

    return true;
}

} // end of namespace bump
