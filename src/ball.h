#ifndef INCLUDE_BALL
#define INCLUDE_BALL

#include "gameobject.h"
#include "vertexarray.h"
#include "texture.h"
#include "collide.h"

namespace bump {

class Game;
class Box;
class Config;

class Ball: public GameObject {
public:
    struct CollideImpact {
        float m_collideTime;
        float m_newCenterX, m_newCenterY;
        float m_newSpeedX, m_newSpeedY;

        CollideImpact& operator=(const CollideImpact& other)
        {
            m_collideTime = other.m_collideTime;
            m_newCenterX = other.m_newCenterX;
            m_newCenterY = other.m_newCenterY;
            m_newSpeedX = other.m_newSpeedX;
            m_newSpeedY = other.m_newSpeedY;
            return *this;
        }
    };

    static bool init(const Config& cfg);

    static float radius()
    {
        return k_radius;
    }

    Ball(Game& game);

    virtual ~Ball();

    void init(float x, float y, float speed);

    virtual void draw(BumpShaderProgram& program);

    bool update(float timeDelta);

    bool collideBat(float& newLeft, float targetLeft);

private:
    bool collideBoundary(CollideImpact& impact, float timeDelta);

    bool collideRect(CollideImpact& impact,
                     float left, float bottom, float right, float top,
                     float timeDelta);

    bool collideBoxMatrix(CollideImpact& impact, Box*& box,
                          int& row, int& col, float timeDelta);

    void getNewSpeed(float& speedX, float& speedY,
                     CollideResult result,
                     float centerX, float centerY,
                     float collideX, float collideY);

    bool getCoveredBox(int& startRow, int& endRow,
                       int& startCol, int& endCol,
                       float timeDelta);

protected:
    static float k_radius;
    static VertexArray k_va;
    static Texture k_texture;

    Game& m_game;
    float m_speed;
    float m_speedX, m_speedY;
};

} // end of namespace bump

#endif

