#ifndef INCLUDE_LINKITEM
#define INCLUDE_LINKITEM

namespace bump {

struct LinkItem {
    LinkItem();

    virtual ~LinkItem();

    LinkItem *m_next;
};

} // end of namespace bump

#endif

