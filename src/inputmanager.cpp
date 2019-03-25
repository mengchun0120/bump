#include <memory>
#include "inputmanager.h"
#include "config.h"

namespace bump {

static std::shared_ptr<InputManager> k_inputManager;

LinkItem *allocPointerEvent()
{
    return new PointerEvent();
}

void deallocPointerEvent(LinkItem *item)
{
    delete item;
}

void handleCursorPos(GLFWwindow *window, double x, double y)
{
    k_inputManager->addPointerEvent((GLfloat)x, (GLfloat)y, PointerEvent::POINTER_MOVE);
}

InputManager &InputManager::singleton()
{
    return *k_inputManager;
}

void InputManager::initSingleton(GLFWwindow *window)
{
    const Config& config = Config::getSingleton();
    k_inputManager.reset(new InputManager(window, config.m_pointerEventPoolSize));
}

InputManager::InputManager(GLFWwindow *window, unsigned int pointerEventPoolSize)
: m_window(window)
, m_mutex()
, m_enabled(false)
, m_pointerEventPool(pointerEventPoolSize, allocPointerEvent, deallocPointerEvent)
, m_inPointerEvents()
{
}

InputManager::~InputManager()
{
}

void InputManager::start()
{
    m_enabled = true;
    glfwSetCursorPosCallback(m_window, handleCursorPos);
}

void InputManager::stop()
{
    m_enabled = false;
    glfwSetCursorPosCallback(m_window, nullptr);
}

void InputManager::addPointerEvent(GLfloat x, GLfloat y, PointerEvent::Type type)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if(!m_enabled) {
        return;
    }

    PointerEvent *event = reinterpret_cast<PointerEvent *>(m_pointerEventPool.alloc());
    event->m_x = x;
    event->m_y = y;
    event->m_type = type;

    m_inPointerEvents.enqueue(event);
}

void InputManager::loadPointerEvent(Queue &q)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if(!m_enabled) {
        return;
    }

    q.join(m_inPointerEvents);
}

void InputManager::freePointerEvent(Queue &q)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    PointerEvent *event;
    while((event = (PointerEvent *)q.dequeue()) != nullptr) {
        m_pointerEventPool.free(event);
    }
}

} // end of namespace bump

