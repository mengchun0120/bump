#include "objectpool.h"

namespace bump {

ObjectPool::ObjectPool()
: m_pool()
, m_capacity(0)
, m_allocFunc(nullptr)
, m_deallocFunc(nullptr)
{
}

ObjectPool::ObjectPool(unsigned int capacity, AllocFunc allocFunc, DeallocFunc deallocFunc)
: m_pool()
, m_capacity(capacity)
, m_allocFunc(allocFunc)
, m_deallocFunc(deallocFunc)
{
}

ObjectPool::~ObjectPool()
{
}

void ObjectPool::init(unsigned int capacity, AllocFunc allocFunc, DeallocFunc deallocFunc)
{
    m_capacity = capacity;
    m_allocFunc = allocFunc;
    m_deallocFunc = deallocFunc;
}

LinkItem* ObjectPool::alloc()
{
    if(m_pool.count() == 0) {
        return m_allocFunc();
    }

    return m_pool.dequeue();
}

void ObjectPool::free(LinkItem* item)
{
    if(m_pool.count() >= m_capacity) {
        m_deallocFunc(item);
    } else {
        m_pool.enqueue(item);
    }
}

} // end of namespace bump

