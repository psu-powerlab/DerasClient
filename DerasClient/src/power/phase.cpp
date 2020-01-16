#include <cmath>
#include "phase.h"

Phase::Phase
    (
        unsigned int volts
    )
    : voltage_(volts), current_(0)
{
    // do nothing
}

Phase::~Phase()
{
    // do nothing
}

std::complex <double>  Phase::GetVoltage()
{
    return voltage_;
}

std::complex <double>  Phase::GetCurrent()
{
    return current_;
}

double Phase::GetActivePower()
{
    return std::real(voltage_*current_);
}

double Phase::GetReactivePower()
{
    return std::imag(voltage_*current_);
}

double Phase::GetApparentPower()
{
    return std::abs(voltage_*current_);
}

double Phase::GetPowerFactor()
{
    return GetActivePower()/GetApparentPower();
}
