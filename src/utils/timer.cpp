#include <utils/timer.h>

#include <iostream>

using namespace Utils;

template <typename T>
std::unique_ptr<T> Singleton<T>::instance_ = nullptr;

template class Utils::Singleton<GlobalTimer>;

void GlobalTimer::Start()
{
    start_ = std::chrono::high_resolution_clock::now();
}

double GlobalTimer::Stop()
{
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> elapsed = end - start_;
    return elapsed.count();
}

void GlobalTimer::PrintElapsedTime()
{
    double elapsed = Stop();
    std::cout << "Elapsed time: " << elapsed << " microseconds" << std::endl;
}