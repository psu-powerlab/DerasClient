#ifndef PHASE_H
#define PHASE_H
#include <complex>

class Phase
{
public:
    Phase
        (
            std::complex <double> volts,
            std::complex <double> amps
        );
    virtual ~Phase();
    std::complex <double> GetVoltage();
    std::complex <double> GetCurrent();
    double GetActivePower();
    double GetReactivePower();
    double GetApparentPower();
    double GetPowerFactor();

private:
    std::complex <double> voltage_;
    std::complex <double> current_;
};

#endif // PHASE_H
