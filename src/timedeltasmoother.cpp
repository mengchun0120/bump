#include "timedeltasmoother.h"

namespace bump {

TimeDeltaSmoother::TimeDeltaSmoother()
{
    using namespace std::chrono;

    const unsigned int HIST_SIZE = 5;

    m_timeDeltaHistory.resize(HIST_SIZE);
}


TimeDeltaSmoother::~TimeDeltaSmoother()
{
}


void TimeDeltaSmoother::start()
{
    using namespace std::chrono;

    m_prevTime = high_resolution_clock::now();

    unsigned int histSize = m_timeDeltaHistory.size();
    for(unsigned int i = 0; i < histSize; ++i) {
        m_timeDeltaHistory[i] = 0.0f;
    }

    m_sumTimeDelta = 0.0f;
    m_lastSlot = 0;
}

float TimeDeltaSmoother::curTimeDelta()
{
    using namespace std::chrono;

    TimePoint curTime = high_resolution_clock::now();
    duration<float> dur = curTime - m_prevTime;
    float timeDelta = dur.count();

    unsigned int histSize = m_timeDeltaHistory.size();

    m_sumTimeDelta += timeDelta - m_timeDeltaHistory[m_lastSlot];
    m_timeDeltaHistory[m_lastSlot] = timeDelta;
    m_lastSlot = (m_lastSlot + 1) % histSize;
    m_prevTime = curTime;

    return m_sumTimeDelta / histSize;
}

} // end of namespace bump
