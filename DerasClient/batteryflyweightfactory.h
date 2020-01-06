#ifndef BATTERYFLYWEIGHTFACTORY_H
#define BATTERYFLYWEIGHTFACTORY_H

#include <iostream>
#include "batterymodel.h"

class AquionModel : public BatteryModel
{
public:
    AquionModel
    (): BatteryModel(40, 60, 48, 120, 19000, 30000, 20000, 27000, "Aquion")
    {
        // do nothing other than init model
    };

};

class SimpliphiModel : public BatteryModel
{
public:
    SimpliphiModel
    (): BatteryModel(48, 56, 51, 225, 22200, 22800, 22200, 22800, "Simpliphi")
    {
        // do nothing other than init model
    };
};

class BatteryFlyweightFactory
{
public:
    BatteryFlyweightFactory ();
    virtual ~BatteryFlyweightFactory ();
    BatteryModel* GetModel (const std::string& type);

private:
    BatteryModel* aquion_;
    BatteryModel* simpliphi_;
};


#endif // BATTERYFLYWEIGHTFACTORY_H
