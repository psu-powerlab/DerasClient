#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>

#include "clock.h"
#include "batteryflyweightfactory.h"
#include "battery.h"

int main()
{
    Clock* clock = Clock::Instance();
    BatteryFlyweightFactory BFF;
    Battery AM48(BFF.GetModel("Aquion"));
    AM48.SetCurrent(-120);
    for (int i=0; i < 100; i++)
    {
        AM48.Update();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
