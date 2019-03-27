#ifndef INCLUDE_SHADERPROGRAM
#define INCLUDE_SHADERPROGRAM

#include <vector>
#include <string>

namespace bump {

class ShaderProgram {
public:
    ShaderProgram(const std::string& vertexShaderFile,
                  const std::string& fragShaderFile);

    virtual ~ShaderProgram();

    void use();

protected:
    bool build(const std::string& vertexShaderFile,
               const std::string& fragShaderFile);

    void destroy();

    unsigned int m_vertexShader;
    unsigned int m_fragShader;
    unsigned int m_program;
};

} // end of namespace bump

#endif
