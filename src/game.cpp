#include <cmath>
#include "log.h"
#include "inputmanager.h"
#include "game.h"

namespace bump {

float toRad(float degree)
{
    return degree * 3.14159265359f / 180.0f;
}

Game::Game(std::shared_ptr<BumpShaderProgram>& program, float width, float height)
: m_state(GAME_RUNNING)
, m_program(program)
, m_width(width)
, m_height(height)
, m_bat(width, height)
, m_ball(*this)
{
    float speed = 200.0f;
    float angle = toRad(45.0f);
    LOG_INFO("%f %f %f", m_bat.y(), m_bat.height(), m_ball.radius());
    m_ball.init(width/2.0f, m_bat.y() + m_bat.height() + m_ball.radius(),
                speed * cos(angle), speed * sin(angle));
}

Game::~Game()
{
}

void Game::update(float timeDelta)
{
    if(m_state != GAME_RUNNING) {
        return;
    }

    process_input();

    if(!m_ball.update(timeDelta)) {
        m_state = GAME_STOP;
    }
}

void Game::present()
{
    m_bat.draw(*m_program);
    m_ball.draw(*m_program);
}

void Game::process_input()
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

} // end of namespace bump

