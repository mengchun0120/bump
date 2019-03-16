#include <memory>
#include "bump_log.h"
#include "bump_app.h"

namespace bump {

static std::shared_ptr<App> g_app;

App& App::getSingleton()
{
    return *g_app;
}

bool App::initSingleton(const Config& cfg)
{
    if(g_app) {
        LOG_ERROR("App singleton already initialized");
        return false;
    }

    App *app = new App();
    if(!app->init(cfg)) {
        LOG_ERROR("Failed to initialize App");
        delete app;
        return false;
    }

    g_app.reset(app);
    return true;
}

App::App()
: m_window(nullptr)
{
}

App::~App()
{
    if(m_window != nullptr) {
        glfwTerminate();
    }
}

bool App::init(const Config& cfg)
{
    if(!initWindow(cfg)) {
        LOG_ERROR("Failed to initialize window");
        return false;
    }

    if(!initOpenGL()) {
        LOG_ERROR("Failed to initialize OpenGL");
        return false;
    }

    return true;
}

bool App::run()
{
    while(glfwWindowShouldClose(m_window) == 0) {
        if(!update()) {
            LOG_ERROR("Failed to update");
            break;
        }

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    return true;
}

bool App::update()
{
    glClear(GL_COLOR_BUFFER_BIT);
    return true;
}

bool App::initWindow(const Config& cfg)
{
    LOG_INFO("Initializing window");

    if(!glfwInit()) {
        LOG_ERROR("Failed to initialize GLFW");
        return false;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(cfg.m_width, cfg.m_height, cfg.m_title.c_str(), NULL, NULL);
    if(m_window == nullptr){
        LOG_ERROR("Failed to open GLFW window");
        return false;
    }

    glfwMakeContextCurrent(m_window);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        LOG_ERROR("Failed to initialize GLEW");
        return false;
    }

    glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);

    return true;
}

bool App::initOpenGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    return true;
}

} // end of namespace bump
