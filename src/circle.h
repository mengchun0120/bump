#ifndef INCLUDE_CIRCLE
#define INCLUDE_CIRCLE

#include "polygon.h"

namespace bump {

class Circle: public Polygon {
public:
    Circle();

    Circle(float centerX, float centerY, float radius, unsigned int numVertices);

    virtual ~Circle();

    bool init(float centerX, float centerY, float radius, unsigned int numVertices);

    float centerX() const
    {
        return m_centerX;
    }

    float centerY() const
    {
        return m_centerY;
    }

    float radius() const
    {
        return m_radius;
    }

protected:
    float m_centerX, m_centerY;
    float m_radius;
};

} // end of namespace bump

#endif
