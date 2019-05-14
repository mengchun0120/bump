#ifndef INCLUDE_APP
#define INCLUDE_APP

#include <memory>
#include "bumpshaderprogram.h"
#include "timedeltasmoother.h"
#include "inputmanager.h"
#include "game.h"

class GLFWwindow;
class Config;

namespace bump {

class App {
public:
    App();

    ~App();

    bool run();

    bool init(const Config& cfg);

    BumpShaderProgram& program()
    {
        return *m_program;
    }

private:

    bool initWindow(const Config& cfg);

    bool initOpenGL(const Config& cfg);

    void updateViewport();

    void initGame(const Config& cfg);

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

