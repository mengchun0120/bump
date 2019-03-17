#ifndef INCLUDE_BUMPSHADERPROGRAM
#define INCLUDE_BUMPSHADERPROGRAM

#include "config.h"
#include "shaderprogram.h"
#include "vertexarray.h"

namespace bump {

class BumpShaderProgram: public ShaderProgram {
public:
    BumpShaderProgram(const std::string& vertexShaderFile, const std::string& fragShaderFile);

    virtual ~BumpShaderProgram();

    bool draw(GLenum mode, const VertexArray& vertexArray, const float color[]);

protected:
    bool loadParam();

    GLint m_posLocation;
    GLint m_colorLocation;
};

} // end of namespace bump

#endif
