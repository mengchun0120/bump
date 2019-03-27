#include <stdexcept>
#include "log.h"
#include "rectangle.h"

namespace bump {

Rectangle::Rectangle()
: Polygon()
{
}

Rectangle::Rectangle(float x, float y, float width, float height)
: Polygon()
, m_x(x)
, m_y(y)
, m_width(width)
, m_height(height)
{
    if(!init(x, y, width, height)) {
        throw std::runtime_error("Failed to initialize Rectangle");
    }
}

Rectangle::~Rectangle()
{
}

bool Rectangle::init(float x, float y, float width, float height)
{
    float vertices[] = {
        x+width/2.0f, y+height/2.0f,
        x, y,
        x, y+height,
        x+width, y+height,
        x+width, y,
        x, y
    };

    if(!load(vertices, 6, nullptr, 0)) {
        return false;
    }

    return true;
}

} // end of namespace bump

