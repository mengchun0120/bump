#include <stdexcept>
#include <GL/glew.h>
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

    k_textures.resize(cfg.m_boxImages.size());
    size_t numBoxes = k_textures.size();
    for(size_t i = 0; i < numBoxes; ++i) {
        if(!k_textures[i].load(cfg.m_boxImages[i])) {
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
}

Box::~Box()
{
}

void Box::draw(BumpShaderProgram& program)
{
    program.setUseObjRef(true);
    program.setObjRef(m_pos);
    program.setPosition(k_va);
    program.setTexture(k_textures[m_type].textureId());
    program.setUseColor(false);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

bool Box::onHit()
{
    if(m_life > 0) {
        --m_life;
    }

    return m_life > 0;
}

} // end of namespace bump

