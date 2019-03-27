#ifndef INCLUDE_RECTANGLE
#define INCLUDE_RECTANGLE

#include "polygon.h"

namespace bump {

class Rectangle: public Polygon {
public:
    Rectangle();

    Rectangle(float x, float y, float width, float height);

    virtual ~Rectangle();

    bool init(float x, float y, float width, float height);

    float x() const
    {
        return m_x;
    }

    float y() const
    {
        return m_y;
    }

    float width() const
    {
        return m_width;
    }

    float height() const
    {
        return m_height;
    }

protected:
    float m_x;
    float m_y;
    float m_width;
    float m_height;
};

} // end of namespace bump

#endif

