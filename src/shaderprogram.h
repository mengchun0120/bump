#ifndef INCLUDE_SHADERPROGRAM
#define INCLUDE_SHADERPROGRAM

#include <GL/glew.h>
#include <vector>
#include <string>

namespace bump {

class ShaderProgram {
public:
    ShaderProgram(const std::string& vertexShaderFile,
                  const std::string& fragShaderFile);

    virtual ~ShaderProgram();

    bool use();

protected:
    bool build(const std::string& vertexShaderFile,
               const std::string& fragShaderFile);

    void destroy();

    GLuint m_vertexShader;
    GLuint m_fragShader;
    GLuint m_program;
};

} // end of namespace bump

#endif
