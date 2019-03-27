#ifndef INCLUDE_APP
#define INCLUDE_APP

#include <memory>
#include "bumpshaderprogram.h"
#include "timedeltasmoother.h"
#include "game.h"

class GLFWwindow;

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
    float m_viewportWidth;
    float m_viewportHeight;
    TimeDeltaSmoother m_deltaSmoother;
    Game* m_game;
};

} // end of namespace bump

#endif

