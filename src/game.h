#ifndef INCLUDE_GAME
#define INCLUDE_GAME

#include <memory>
#include "ball.h"
#include "bat.h"
#include "boxmatrix.h"

namespace bump {

class Queue;

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

    void update(Queue& queue, float timeDelta);

    void present();

    float clampX(float x) const;

    float clampY(float y) const;

    const Bat& bat() const
    {
        return m_bat;
    }

    Bat& bat()
    {
        return m_bat;
    }

    const Ball& ball() const
    {
        return m_ball;
    }

    Ball& ball()
    {
        return m_ball;
    }

    BoxMatrix& boxMatrix()
    {
        return m_boxMatrix;
    }

private:
    void process_input(Queue& queue);

private:
    static const unsigned int NUM_BOX_ROWS = 5;
    static const unsigned int NUM_BOX_COLS = 7;

    State m_state;
    std::shared_ptr<BumpShaderProgram> m_program;
    float m_width;
    float m_height;
    Bat m_bat;
    Ball m_ball;
    BoxMatrix m_boxMatrix;
};

} // end of namespace bump

#endif

