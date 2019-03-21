#ifndef INCLUDE_CONSTANTS
#define INCLUDE_CONSTANTS

namespace bump {

class Constants {
public:
    static const unsigned int NUM_FLOATS_PER_VERTEX = 2;
    static const unsigned int VERTEX_SIZE = sizeof(float) * NUM_FLOATS_PER_VERTEX;
    static const unsigned int NUM_FLOATS_COLOR = 4;
};

} // end of namespace bump


#endif
