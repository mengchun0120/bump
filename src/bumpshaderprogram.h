#ifndef INCLUDE_BUMPSHADERPROGRAM
#define INCLUDE_BUMPSHADERPROGRAM

#include "config.h"
#include "shaderprogram.h"

namespace bump {

class BumpShaderProgram: public ShaderProgram {
public:
    BumpShaderProgram(const std::string& vertexShaderFile, const std::string& fragShaderFile);

    virtual ~BumpShaderProgram();

protected:
    bool loadParam();

    GLint m_posLocation;
    GLint m_colorLocation;
};

} // end of namespace bump

#endif
