#ifndef INCLUDE_TIMEDELTASMOOTHER
#define INCLUDE_TIMEDELTASMOOTHER

#include <vector>
#include <chrono>

namespace bump {

class TimeDeltaSmoother {
public:
    typedef std::chrono::high_resolution_clock::time_point TimePoint;

    TimeDeltaSmoother();

    virtual ~TimeDeltaSmoother();

    void start();

    float getTimeDelta();

private:
    std::vector<float> m_timeDeltaHistory;
    float m_sumTimeDelta;
    unsigned int m_totalSlots;
    unsigned int m_lastSlot;
    TimePoint m_prevTime;
};

} // end of namespace bump

#endif

