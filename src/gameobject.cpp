#include "gameobject.h"

namespace bump {

GameObject::GameObject()
{
    m_pos[0] = 0.0f;
    m_pos[1] = 0.0f;
}

GameObject::GameObject(float x, float y)
{
    m_pos[0] = x;
    m_pos[1] = y;
}

GameObject::~GameObject()
{
}

} // end of namespace bump

