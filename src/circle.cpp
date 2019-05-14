#include <cmath>
#include <stdexcept>
#include "log.h"
#include "circle.h"

namespace bump {

Circle::Circle()
: Polygon()
{
}

Circle::Circle(float centerX, float centerY, float radius, unsigned int numVertices)
: Polygon()
, m_centerX(centerX)
, m_centerY(centerY)
, m_radius(radius)
{
    if(!init(centerX, centerY, radius, numVertices)) {
        throw std::runtime_error("Failed to initialize circle");
    }
}

Circle::~Circle()
{

}

bool Circle::init(float centerX, float centerY, float radius, unsigned int numVertices)
{
    const double PI = 3.14159265359;
    const double DELTA = 2.0 * PI / numVertices;

    float vertices[Constants::NUM_FLOATS_PER_POSITION * (numVertices+2)];
    unsigned int i, j;
    double theta = 0;

    vertices[0] = centerX;
    vertices[1] = centerY;
    for(i = 0, j = 2; i <= numVertices; ++i, j+=2) {
        vertices[j] = centerX + radius * cos(theta);
        vertices[j+1] = centerY + radius * sin(theta);
        theta += DELTA;
    }

    return load(vertices, numVertices+2, false, nullptr, 0);
}

} // end of namespace bump

