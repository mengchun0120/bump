#include "inputmanager.h"
#include "game.h"
#include <iostream>

namespace bump {

Game::Game(std::shared_ptr<BumpShaderProgram>& program, GLfloat width, GLfloat height)
: m_program(program)
, m_width(width)
, m_height(height)
, m_bat(width, height)
{


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
}

} // end of namespace bump
