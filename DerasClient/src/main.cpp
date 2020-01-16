#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>
#include <complex>

#include "utility/clock.h"
#include "battery/batteryflyweightfactory.h"
#include "battery/battery.h"
#include "inverter/inverterflyweightfactory.h"

int main()
{
    Clock* clock = Clock::Instance();
    BatteryFlyweightFactory BFF;
    Battery AM48(BFF.GetModel("Aquion"));

    InverterFlyweightFactory IFF;

    AM48.SetCurrent(-120);
    for (int i=0; i < 100; i++)
    {
        AM48.Update();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
