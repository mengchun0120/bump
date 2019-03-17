#ifndef INCLUDE_APP
#define INCLUDE_APP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "bumpshaderprogram.h"

namespace bump {

class App {
public:
    static App& getSingleton();

    static bool initSingleton();

    ~App();

    bool run();

private:
    App();

    bool init();

    bool initWindow();

    bool initOpenGL();

    void updateOpenGLForUse();

private:
    GLFWwindow* m_window;
    BumpShaderProgram* m_program;
};

} // end of namespace bump

#endif
