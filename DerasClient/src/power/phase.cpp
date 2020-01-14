#include <cmath>
#include "phase.h"

Phase::Phase
    (
        const std::complex <float>& volts,
        const std::complex <float>& amps
    )
    : voltage_(volts), current_(amps)
{
    // do nothing
}

Phase::~Phase()
{
    // do nothing
}

std::complex <float>  Phase::GetVoltage()
{
    return voltage_;
}

std::complex <float>  Phase::GetCurrent()
{
    return current_;
}

float Phase::GetActivePower()
{
    return std::real(voltage_*current_);
}

float Phase::GetReactivePower()
{
    return std::imag(voltage_*current_);
}

float Phase::GetApparentPower()
{
    return std::abs(voltage_*current_);
}

float Phase::GetPowerFactor()
{
    return std::acos(std::abs(current_)/std::abs(voltage_));
}
