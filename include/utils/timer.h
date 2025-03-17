#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <utils/singleton.h>

namespace Utils
{
    class GlobalTimer : public Singleton<GlobalTimer>
    {
        friend class Singleton<GlobalTimer>;

    public:
        void Start();                                                   // Start the timer
        double Stop();                                                  // Stop the timer and return the elapsed time

        void PrintElapsedTime();

        ~GlobalTimer() = default;

    protected:
        GlobalTimer() = default;

    private:
        std::chrono::high_resolution_clock::time_point start_;
    };
}

#endif // TIMER_H