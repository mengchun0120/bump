#include "pointerevent.h"

namespace bump {

PointerEvent::PointerEvent()
: LinkItem()
, m_x(0)
, m_y(0)
, m_type(POINTER_UNKNOWN)
{
}

PointerEvent::PointerEvent(GLfloat x, GLfloat y, Type type)
: LinkItem()
, m_x(x)
, m_y(y)
, m_type(type)
{
}

} // end of namespace bump

