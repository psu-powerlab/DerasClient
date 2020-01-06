#include "clock.h"
#include <chrono>
#include <ctime>
#include <iostream>

using namespace std::chrono;

Clock::Clock() : offset_ (0)
{
    // do nothing
    std::cout << "[CLOCK]\n... constructed"
        << "\n... " << Clock::GetDateTime() << std::endl;
}

Clock* Clock::Instance()
{
    // c++11 will only run this one.
    static Clock* instance = new Clock();
    return instance;
}

unsigned long long int Clock::GetUtc ()
{
    auto device = std::chrono::seconds(std::time(nullptr)) + seconds(offset_);
    return device.count();
}

std::string Clock::GetTime ()
{
    auto time_point = system_clock::now() + seconds(offset_);
    std::time_t now = system_clock::to_time_t (time_point);

    std::string s(30, '\0');
    std::strftime(&s[0], s.size(), "%H:%M:%S", std::localtime(&now));
    return s;
}

std::string Clock::GetDate ()
{
    auto time_point = system_clock::now() + seconds(offset_);
    std::time_t now = system_clock::to_time_t (time_point);

    std::string s(30, '\0');
    std::strftime(&s[0], s.size(), "%Y-%m-%d", std::localtime(&now));
    return s;
}

std::string Clock::GetDateTime ()
{
    auto time_point = system_clock::now() + seconds(offset_);
    std::time_t now = system_clock::to_time_t (time_point);

    std::string s(30, '\0');
    std::strftime(&s[0], s.size(), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return s;
}

void Clock::Synchronize (const unsigned long long int& time)
{
    auto server = std::chrono::seconds(time);
    auto device = std::chrono::seconds(std::time(nullptr));
    offset_ = (device - server).count();
}
