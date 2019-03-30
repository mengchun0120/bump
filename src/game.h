#ifndef INCLUDE_GAME
#define INCLUDE_GAME

#include <memory>
#include "bat.h"
#include "ball.h"

namespace bump {

class Game {
public:
    enum State {
        GAME_RUNNING,
        GAME_STOP
    };

public:
    Game(std::shared_ptr<BumpShaderProgram>& program, float width, float height);

    virtual ~Game();

    float width() const
    {
        return m_width;
    }

    float height() const
    {
        return m_height;
    }

    void update(float timeDelta);

    void present();

private:
    void process_input();

private:
    State m_state;
    std::shared_ptr<BumpShaderProgram> m_program;
    float m_width;
    float m_height;
    Bat m_bat;
    Ball m_ball;
};

} // end of namespace bump

#endif

