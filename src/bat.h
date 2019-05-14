#ifndef INCLUDE_BAT
#define INCLUDE_BAT

#include "gameobject.h"
#include "vertexarray.h"
#include "texture.h"

namespace bump {

class Game;

class Bat: public GameObject {
public:
    static bool init(const Config& cfg);

    static float width()
    {
        return k_width;
    }

    static float height()
    {
        return k_height;
    }

    Bat(Game& game);

    virtual ~Bat();

    virtual void draw(BumpShaderProgram& program);

    void move(float newX);

    float right() const
    {
        return m_pos[0] + k_width;
    }

    float top() const
    {
        return m_pos[1] + k_height;
    }

protected:
    static float k_width;
    static float k_height;
    static VertexArray k_va;
    static Texture k_texture;

    Game& m_game;
    float m_xBound;
};

} // end of namespace bump

#endif

