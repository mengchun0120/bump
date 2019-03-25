#ifndef INCLUDE_POINTEREVENT
#define INCLUDE_POINTEREVENT

#include <GL/glew.h>
#include "linkitem.h"

namespace bump {

class PointerEvent: public LinkItem {
public:
    enum Type {
        POINTER_DOWN,
        POINTER_UP,
        POINTER_MOVE,
        POINTER_UNKNOWN
    };

    PointerEvent();

    PointerEvent(GLfloat x, GLfloat y, Type type);

public:
    GLfloat m_x, m_y;
    Type m_type;
};

} // end of namespace bump

#endif

