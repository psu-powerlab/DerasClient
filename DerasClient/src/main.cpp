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
#include "power/phase.h"

int main()
{
    float pi = std::acos(-1);
    float r = 10;
    std::complex <float> volts = std::polar(r, pi);
    std::complex <float> amps = std::polar(r, pi/4);
    Phase A(volts, amps);
    std::cout << A.GetActivePower() << ", " << A.GetApparentPower() << ", " << A.GetPowerFactor() << std::endl;
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
