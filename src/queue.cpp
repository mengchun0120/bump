#include "queue.h"

namespace bump {

Queue::Queue()
: m_first(nullptr)
, m_last(nullptr)
, m_count(0)
{
}

Queue::~Queue()
{
    LinkItem *next, *item;
    for(item = m_first; item != nullptr; item = next) {
        next = item->m_next;
        delete item;
    }
}

LinkItem *Queue::dequeue()
{
    if(m_first == nullptr) {
        return nullptr;
    }

    LinkItem *item = m_first;

    m_first = m_first->m_next;
    if(m_first == nullptr) {
        m_last = nullptr;
    }
    --m_count;

    item->m_next = nullptr;
    return item;
}

void Queue::enqueue(LinkItem* item)
{
    item->m_next = nullptr;

    if(m_last == nullptr) {
        m_first = item;
        m_last = item;
    } else {
        m_last->m_next = item;
        m_last = item;
    }

    ++m_count;
}

void Queue::join(Queue &q)
{
    if(m_last) {
        m_last->m_next = q.m_first;
    } else {
        m_first = q.m_first;
    }
    m_last = q.m_last;
    m_count += q.m_count;

    q.m_first = q.m_last = nullptr;
    q.m_count = 0;
}

} // end of namespace bump

