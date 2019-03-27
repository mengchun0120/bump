#include <cmath>
#include "log.h"
#include "inputmanager.h"
#include "game.h"

namespace bump {

float toRad(float degree)
{
    return degree / 3.14159265359f;
}

Game::Game(std::shared_ptr<BumpShaderProgram>& program, float width, float height)
: m_program(program)
, m_width(width)
, m_height(height)
, m_bat(width, height)
, m_ball()
{
    float speed = 10.0f;
    float angle = toRad(45.0f);
    LOG_INFO("%f %f %f", m_bat.y(), m_bat.height(), m_ball.radius());
    m_ball.init(width/2.0f, m_bat.y() + m_bat.height() + m_ball.radius(),
                speed * cos(speed), speed * sin(speed));
}

Game::~Game()
{
}

void Game::update()
{
    InputManager& inputManager = InputManager::singleton();
    Queue queue;

    inputManager.loadPointerEvent(queue);

    PointerEvent *event = reinterpret_cast<PointerEvent *>(queue.first());
    while(event) {
        m_bat.move(event->m_x);
        event = reinterpret_cast<PointerEvent *>(event->m_next);
    }

    inputManager.freePointerEvent(queue);
}

void Game::present()
{
    m_bat.draw(*m_program);
    m_ball.draw(*m_program);
}

} // end of namespace bump

