#include <iostream>
#include <cstdlib>
#include "batteryflyweightfactory.h"

BatteryFlyweightFactory::BatteryFlyweightFactory()
    : aquion_(nullptr), simpliphi_(nullptr)
{
   // do nothing
   std::cout << "[BATTERY FACTORY]\n... constructed\n";
}

BatteryFlyweightFactory::~BatteryFlyweightFactory()
{
    // do nothing
}

BatteryModel* BatteryFlyweightFactory::GetModel(const std::string& type)
{
    if (type == "Aquion")
    {
        if (!aquion_)
        {
            std::cout << "[BATTERY FACTORY]\n... building Aquion model\n";
            aquion_ = new AquionModel();
        }
        return aquion_;
    }
    else if (type == "Simpliphi")
    {
        if (!simpliphi_)
        {
            std::cout << "[BATTERY FACTORY]\n... building Simpliphi model\n";
            simpliphi_ = new SimpliphiModel();
        }
        return simpliphi_;
    }
    else
    {
        std::cout << "[BATTERY FACTORY]\n... unknown model selected\n";
        exit(0);
    }
}
