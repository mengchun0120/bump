#ifndef INCLUDE_INPUTMANAGER
#define INCLUDE_INPUTMANAGER

#include <mutex>
#include "objectpool.h"
#include "pointerevent.h"
#include <GLFW/glfw3.h>

namespace bump {

class InputManager {
public:
    static InputManager &singleton();

    static void initSingleton(GLFWwindow *window, unsigned int pointerEventPoolSize);

    virtual ~InputManager();

    void start();

    void stop();

    void addPointerEvent(GLfloat x, GLfloat y, PointerEvent::Type type);

    void loadPointerEvent(Queue &q);

    void freePointerEvent(Queue &q);

protected:
    InputManager(GLFWwindow *window, unsigned int pointerEventPoolSize);

protected:
    GLFWwindow *m_window;
    std::mutex m_mutex;
    bool m_enabled;
    ObjectPool m_pointerEventPool;
    Queue m_inPointerEvents;
    GLfloat m_windowHeight;
};

} // end of namespace bump

#endif

