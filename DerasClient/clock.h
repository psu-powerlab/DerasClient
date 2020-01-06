#ifndef CLOCK_H
#define CLOCK_H

#include <string>
#include <chrono>

// SINGLETON PATTERN
class Clock
{
    public:
        static Clock* Instance ();
        unsigned long long int GetUtc ();
        std::string GetTime ();
        std::string GetDate ();
        std::string GetDateTime ();
        void Synchronize (const unsigned long long int& server_time);

    private:
        Clock ();
        int offset_;
};

#endif // CLOCK_H
