#ifndef INCLUDE_BUMPSHADERPROGRAM
#define INCLUDE_BUMPSHADERPROGRAM

#include "shaderprogram.h"
#include "vertexarray.h"

namespace bump {

class BumpShaderProgram: public ShaderProgram {
public:
    BumpShaderProgram(const std::string & vertexShaderFile, const std::string & fragShaderFile);

    virtual ~BumpShaderProgram();

    void setUseObjRef(bool enabled);

    void setObjRef(const float *objRef);

    void setViewportSize(const float *viewportSize);

    void setViewportOrigin(const float *viewportOrigin);

    void setPosition(const VertexArray &vertexArray);

    void setColor(const float *color);

protected:
    void loadParam();

    int m_positionLocation;
    int m_useObjRefLocation;
    int m_objRefLocation;
    int m_viewportSizeLocation;
    int m_viewportOriginLocation;
    int m_colorLocation;
};

} // end of namespace bump

#endif

