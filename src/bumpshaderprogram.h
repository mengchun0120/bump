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

    void setUseObjRef(bool enabled)
    {
        glUniform1i(m_useObjRefLocation, enabled ? 1 : 0);
    }

    void setObjRef(const GLfloat* objRef)
    {
        glUniform2fv(m_objRefLocation, 1, objRef);
    }

    void setViewportSize(const GLfloat* viewportSize)
    {
        glUniform2fv(m_viewportSizeLocation, 1, viewportSize);
    }

    void setViewportOrigin(const GLfloat* viewportOrigin)
    {
        glUniform2fv(m_viewportOriginLocation, 1, viewportOrigin);
    }

    void setPosition(const VertexArray& vertexArray);

protected:
    void loadParam();

    GLint m_positionLocation;
    GLint m_useObjRefLocation;
    GLint m_objRefLocation;
    GLint m_viewportSizeLocation;
    GLint m_viewportOriginLocation;
    GLint m_colorLocation;
};

} // end of namespace bump

#endif
