#ifndef INCLUDE_BUMP_APP
#define INCLUDE_BUMP_APP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "bump_config.h"

namespace bump {

class App {
public:
    static App& getSingleton();

    static bool initSingleton(const Config& cfg);

    ~App();

    bool init(const Config& cfg);

    bool run();

private:
    App();

    bool initWindow(const Config& cfg);

    bool initOpenGL();

    bool update();

private:
    GLFWwindow* m_window;
};

} // end of namespace bump

#endif
