#ifndef INCLUDE_BOX
#define INCLUDE_BOX

#include <vector>
#include "texture.h"
#include "vertexarray.h"
#include "gameobject.h"

namespace bump {

class Config;

class Box: public GameObject {
public:
    static float width()
    {
        return k_width;
    }

    static float height()
    {
        return k_height;
    }

    static unsigned int typeCount()
    {
        return k_maxLife.size();
    }

    static bool init(const Config& cfg);

    Box(float x, float y, int type);

    virtual ~Box();

    virtual void draw(BumpShaderProgram& program);

    float right() const
    {
        return m_pos[0] + k_width;
    }

    float top() const
    {
        return m_pos[1] + k_height;
    }

    bool onHit();

    int life() const
    {
        return m_life;
    }

    int type() const
    {
        return m_type;
    }

private:
    static VertexArray k_va;
    static std::vector<Texture> k_textures;
    static float k_width;
    static float k_height;
    static std::vector<int> k_maxLife;

    int m_type;
    int m_life;
};

} // end of namespace bump

#endif

