#include <cmath>
#include <cstdlib>
#include <ctime>
#include "log.h"
#include "inputmanager.h"
#include "ball.h"
#include "bat.h"
#include "box.h"
#include "game.h"

namespace bump {

Game::Game(std::shared_ptr<BumpShaderProgram>& program, float width, float height)
: m_state(GAME_RUNNING)
, m_program(program)
, m_width(width)
, m_height(height)
, m_bat(*this)
, m_ball(*this)
, m_boxMatrix(*this)
{
    float speed = 200.0f;
    m_ball.init(width/2.0f,
                m_bat.y() + m_bat.height() + m_ball.radius(),
                speed);
}

Game::~Game()
{
}

void Game::update(Queue& queue, float timeDelta)
{
    if(m_state != GAME_RUNNING) {
        return;
    }

    process_input(queue);

    if(!m_ball.update(timeDelta)) {
        // Game failed
        m_state = GAME_STOP;
        return;
    }

    if(m_boxMatrix.boxCount() == 0) {
        // Clear all the box
        m_state = GAME_STOP;
        return;
    }
}

void Game::present()
{
    m_boxMatrix.draw(*m_program);
    m_bat.draw(*m_program);
    m_ball.draw(*m_program);
}

void Game::process_input(Queue& queue)
{
    PointerEvent *event = reinterpret_cast<PointerEvent *>(queue.first());
    while(event) {
        m_bat.move(event->m_x);
        event = reinterpret_cast<PointerEvent *>(event->m_next);
    }
}

float Game::clampX(float x) const
{
    if(x < 0.0f) {
        return 0.0f;
    } else if(x > m_width) {
        return m_width;
    }
    return x;
}

float Game::clampY(float y) const
{
    if(y < 0.0f) {
        return 0.0f;
    } else if(y > m_height) {
        return m_height;
    }
    return y;
}

} // end of namespace bump

