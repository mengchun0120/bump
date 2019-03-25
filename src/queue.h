#ifndef INCLUDE_QUEUE
#define INCLUDE_QUEUE

#include "linkitem.h"

namespace bump {

class Queue {
public:
    Queue();

    virtual ~Queue();

    LinkItem* first()
    {
        return m_first;
    }

    const LinkItem *first() const
    {
        return m_first;
    }

    unsigned int count() const
    {
        return m_count;
    }

    LinkItem *dequeue();

    void enqueue(LinkItem *item);

    void join(Queue &q);

protected:
    LinkItem *m_first, *m_last;
    unsigned int m_count;
};

} // end of namespace bump

#endif

