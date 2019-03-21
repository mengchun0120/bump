#ifndef INCLUDE_GAME
#define INCLUDE_GAME

#include <memory>
#include "bat.h"

namespace bump {

class Game {
public:
    Game(std::shared_ptr<BumpShaderProgram>& program, GLfloat width, GLfloat height);

    virtual ~Game();

    GLfloat width() const
    {
        return m_width;
    }

    GLfloat height() const
    {
        return m_height;
    }

    void update();

    void present();

private:
    std::shared_ptr<BumpShaderProgram> m_program;
    GLfloat m_width;
    GLfloat m_height;
    Bat m_bat;
};

} // end of namespace bump

#endif

