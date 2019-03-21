#include "game.h"

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
}

void Game::present()
{
    m_bat.draw(*m_program);
}

} // end of namespace bump
