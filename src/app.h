#ifndef INCLUDE_APP
#define INCLUDE_APP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "bumpshaderprogram.h"
#include "game.h"

namespace bump {

class App {
public:
    static App& getSingleton();

    static bool initSingleton();

    ~App();

    bool run();

    BumpShaderProgram& program()
    {
        return *m_program;
    }

private:
    App();

    bool init();

    bool initWindow();

    bool initOpenGL();

    void updateViewport();

    void initGame();

private:
    GLFWwindow* m_window;
    std::shared_ptr<BumpShaderProgram> m_program;
    GLfloat m_viewportWidth;
    GLfloat m_viewportHeight;
    Game* m_game;
};

} // end of namespace bump

#endif

