#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "log.h"
#include "config.h"
#include "rectangle.h"
#include "circle.h"
#include "inputmanager.h"
#include "box.h"
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
, m_game(nullptr)
{
    if(!init()) {
        throw std::runtime_error("Failed to initialize App");
    }
}

App::~App()
{
    if(m_game != nullptr) {
        delete m_game;
    }

    if(m_window != nullptr) {
        glfwTerminate();
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

    InputManager::initSingleton(m_window);

    initGame();

    return true;
}

bool App::run()
{
    Queue queue;
    InputManager& inputManager = InputManager::singleton();
    float delta;

    while(glfwWindowShouldClose(m_window) == 0) {
        glClear(GL_COLOR_BUFFER_BIT);

        delta = m_deltaSmoother.getTimeDelta();
        inputManager.loadPointerEvent(queue);

        m_game->update(queue, delta);
        m_game->present();

        inputManager.freePointerEvent(queue);

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
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
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
        m_program.reset(new BumpShaderProgram(config.m_bumpVertexShaderFile,
                                              config.m_bumpFragShaderFile));
    } catch(const std::exception& e) {
        LOG_ERROR("Exception happened: %s", e.what());
        return false;
    }

    m_program->use();

    updateViewport();

    return true;
}

void App::updateViewport()
{
    int width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
    glViewport(0, 0, width, height);

    m_viewportWidth = static_cast<float>(width);
    m_viewportHeight = static_cast<float>(height);

    float viewportSize[] = {m_viewportWidth, m_viewportHeight};
    float viewportOrigin[] = {-m_viewportWidth/2.0f, -m_viewportHeight/2.0f};

    m_program->setViewportSize(viewportSize);
    m_program->setViewportOrigin(viewportOrigin);
}

void App::initGame()
{
    Box::initShape();
    m_game = new Game(m_program, m_viewportWidth, m_viewportHeight);
    InputManager::singleton().start();
    m_deltaSmoother.start();
}

} // end of namespace bump

