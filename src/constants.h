#ifndef INCLUDE_CONSTANTS
#define INCLUDE_CONSTANTS

namespace bump {

class Constants {
public:
    static const unsigned int NUM_FLOATS_PER_VERTEX = 2;
    static const unsigned int VERTEX_SIZE = sizeof(float) * NUM_FLOATS_PER_VERTEX;
};

} // end of namespace bump


#endif
