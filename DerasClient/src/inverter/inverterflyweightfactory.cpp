#include <iostream>
#include "inverterflyweightfactory.h"

InverterFlyweightFactory::InverterFlyweightFactory()
    : outback_radian_8048a_(nullptr)
{
    std::cout << "[INVERTER FACTORY]\n... constructed\n";
}

InverterFlyweightFactory::~InverterFlyweightFactory()
{
    //dtor
}

InverterModel* InverterFlyweightFactory::GetModel(const std::string& type)
{
    if (type == "Outback_Radian_8048A")
    {
        if (!outback_radian_8048a_)
        {
            std::cout << "[INVERTER FACTORY]\n... building " << type << "\n";
            outback_radian_8048a_ = new OutbackRadian8048AModel();
        }
        return outback_radian_8048a_;
    }
    else
    {
        std::cout << "[BATTERY FACTORY]\n... unknown model selected\n";
        exit(0);
    }
}
