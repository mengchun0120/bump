#include <stdexcept>
#include <cstring>
#include <GL/glew.h>
#include "log.h"
#include "config.h"
#include "game.h"
#include "bat.h"

namespace bump {

float Bat::k_width;
float Bat::k_height;
VertexArray Bat::k_va;
Texture Bat::k_texture;

bool Bat::init(const Config& cfg)
{
    k_width = cfg.m_batWidth;
    k_height = cfg.m_batHeight;

    if(!VertexArray::loadRectVertexArray(k_va, k_width, k_height)) {
        LOG_ERROR("Failed to load vertex array for Bat");
        return false;
    }

    if(!k_texture.load(cfg.m_batImage)) {
        LOG_ERROR("Failed to load texture for Bat");
        return false;
    }

    return true;
}

Bat::Bat(Game& game)
: GameObject()
, m_game(game)
{
    m_xBound = m_game.width() - k_width;
    m_pos[0] = (m_game.width() - k_width) / 2.0f;
    m_pos[1] = 0.0f;
}

Bat::~Bat()
{
}

void Bat::move(float newX)
{
    if(newX < 0.0f) {
        newX = 0.0f;
    } else if(newX > m_xBound) {
        newX = m_xBound;
    }

    bool collideBall = m_game.ball().collideBat(m_pos[0], newX);
    if(!collideBall) {
        m_pos[0] = newX;
    }
}

void Bat::draw(BumpShaderProgram& program)
{
    program.setUseObjRef(true);
    program.setObjRef(m_pos);
    program.setUseColor(false);
    program.setPosition(k_va);
    program.setTexture(k_texture.textureId());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

} // end of namespace bump

