#include <memory>
#include "log.h"
#include "config.h"
#include "rectangle.h"
#include "app.h"

namespace bump {

static std::shared_ptr<App> g_app;

App& App::getSingleton()
{
    return *g_app;
}

bool App::initSingleton()
{
    if(g_app) {
        LOG_ERROR("App singleton already initialized");
        return false;
    }

    try {
        g_app.reset(new App());
        return true;
    } catch(const std::exception& e) {
        LOG_ERROR("Exception happened %s", e.what());
        return false;
    }
}

App::App()
: m_window(nullptr)
, m_program(nullptr)
{
    if(!init()) {
        throw std::runtime_error("Failed to initialize App");
    }
}

App::~App()
{
    if(m_window != nullptr) {
        glfwTerminate();
    }

    if(m_program != nullptr) {
        delete m_program;
    }
}

bool App::init()
{
    if(!initWindow()) {
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
    updateOpenGLForUse();

    Rectangle rect(0.0f, 0.0f, 100.0f, 100.0f);
    GLfloat ref[] = {100.f, 100.f};
    GLfloat fillColor[] = {1.0f, 0.0f, 0.0f, 1.0f};
    GLfloat borderColor[] = {0.0f, 0.0f, 1.0f, 1.0f};
    
    while(glfwWindowShouldClose(m_window) == 0) {
        glClear(GL_COLOR_BUFFER_BIT);

        rect.draw(*m_program, ref, fillColor, borderColor, 1.0f);

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    return true;
}

bool App::initWindow()
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

    Config& config = Config::getSingleton();

    m_window = glfwCreateWindow(config.m_width, config.m_height, config.m_title.c_str(), NULL, NULL);
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

    try {
        Config& config = Config::getSingleton();
        m_program = new BumpShaderProgram(config.m_bumpVertexShaderFile, config.m_bumpFragShaderFile);
    } catch(const std::exception& e) {
        LOG_ERROR("Exception happened: %s", e.what());
        return false;
    }


    return true;
}

void App::updateOpenGLForUse()
{
    int width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
    glViewport(0, 0, width, height);

    m_program->use();

    GLfloat viewportSize[] = {(GLfloat)width, (GLfloat)height};
    GLfloat viewportOrigin[] = {-(GLfloat)width/2.0f, -(GLfloat)height/2.0f};

    m_program->setViewportSize(viewportSize);
    m_program->setViewportOrigin(viewportOrigin);
}

} // end of namespace bump
