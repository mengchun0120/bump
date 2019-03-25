#ifndef INCLUDE_OBJECTPOOL
#define INCLUDE_OBJECTPOOL

#include "queue.h"

namespace bump {

class ObjectPool {
public:
    typedef LinkItem* (*AllocFunc)();
    typedef void (*DeallocFunc)(LinkItem *item);

    ObjectPool();

    ObjectPool(unsigned int capacity, AllocFunc allocFunc, DeallocFunc deallocFunc);

    virtual ~ObjectPool();

    void init(unsigned int capacity, AllocFunc allocFunc, DeallocFunc deallocFunc);

    LinkItem* alloc();

    void free(LinkItem* item);

protected:
    Queue m_pool;
    unsigned int m_capacity;
    AllocFunc m_allocFunc;
    DeallocFunc m_deallocFunc;
};

} // end of namespace bump

#endif

