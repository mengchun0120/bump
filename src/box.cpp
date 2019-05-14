#include <stdexcept>
#include "log.h"
#include "config.h"
#include "box.h"

namespace bump {

VertexArray Box::k_va;
std::vector<Texture> Box::k_textures;
float Box::k_width;
float Box::k_height;
std::vector<int> Box::k_maxLife;

bool Box::init(const Config& cfg)
{
    k_width = cfg.m_boxWidth;
    k_height = cfg.m_boxHeight;

    if(!VertexArray::loadRectVertexArray(k_va, k_width, k_height)) {
        LOG_ERROR("Failed to initialize VertexArray for Box");
        return false;
    }

    for(auto it = cfg.m_boxImages.begin(); it != cfg.m_boxImages.end(); ++it) {
        k_textures.emplace_back();
        if(!k_textures.back().load(*it)) {
            LOG_ERROR("Failed to initialize textures for Box");
            return false;
        }
    }

    k_maxLife = cfg.m_boxMaxLife;

    return true;
}

Box::Box(float x, float y, int type)
{
    if(type < 0 || type >= k_maxLife.size()) {
        throw std::runtime_error("type out of bounds");
    }

    m_type = type;
    m_pos[0] = x;
    m_pos[1] = y;
    m_life = k_maxLife[type];
    for(unsigned int i = 0; i < Constants::NUM_FLOATS_COLOR; ++i) {
        m_color[i] = k_colors[m_type][i];
    }
}

Box::~Box()
{
}

void Box::draw(BumpShaderProgram& program)
{
    program.setUseObjRef(true);
    program.setObjRef(m_pos);
    program.setPosition(k_va);
    program.setTexture(k_texture[m_type].textureId());
    program.setUseColor(false);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

bool Box::onHit()
{
    if(m_life > 0) {
        --m_life;
        m_color[3] -= 1.0f / (float)k_maxLife[m_type];
    }

    return m_life > 0;
}

} //i end of namespace bump

