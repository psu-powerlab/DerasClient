#ifndef INVERTERFLYWEIGHTFACTORY_H
#define INVERTERFLYWEIGHTFACTORY_H

#include "invertermodel.h"

class OutbackRadian8048AModel : public InverterModel
{
public:
    OutbackRadian8048AModel() : InverterModel (240, 30, 60, 64, 40, 115, "Outback_Radian_8048A")
    {
        // do nothing
    };

};

class InverterFlyweightFactory
{
public:
    InverterFlyweightFactory();
    virtual ~InverterFlyweightFactory();
    InverterModel* GetModel (const std::string& type);

private:
    InverterModel* outback_radian_8048a_;
};

#endif // INVERTERFLYWEIGHTFACTORY_H
