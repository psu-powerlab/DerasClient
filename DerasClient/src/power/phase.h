#ifndef PHASE_H
#define PHASE_H
#include <complex>

class Phase
{
public:
    Phase
        (
            const std::complex <float>& volts,
            const std::complex <float>& amps
        );
    virtual ~Phase();
    std::complex <float> GetVoltage();
    std::complex <float> GetCurrent();
    float GetActivePower();
    float GetReactivePower();
    float GetApparentPower();
    float GetPowerFactor();

private:
    std::complex <float> voltage_;
    std::complex <float> current_;
};

#endif // PHASE_H
