#include "pointofcommoncoupling.h"

PointOfCommonCoupling::PointOfCommonCoupling
    (const float& volts, const float& hertz)
    :
        gen_(rd_()),
        voltage_dist_(volts, volts/100),
        frequency_dist_(hertz, hertz/1000)
{
    // do nothing
}

PointOfCommonCoupling::~PointOfCommonCoupling()
{
    //dtor
}

float PointOfCommonCoupling::GetVoltage()
{
    return voltage_dist_(gen_);
}

float PointOfCommonCoupling::GetFrequency()
{
    return frequency_dist_(gen_);;
}
