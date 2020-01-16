#ifndef POINTOFCOMMONCOUPLING_H
#define POINTOFCOMMONCOUPLING_H

#include <random>

class PointOfCommonCoupling
{
public:
    PointOfCommonCoupling(const float& volts, const float& hertz);
    virtual ~PointOfCommonCoupling();
    float GetVoltage ();
    float GetFrequency ();

private:
    std::random_device rd_;
    std::mt19937 gen_;
    std::normal_distribution<> voltage_dist_;
    std::normal_distribution<> frequency_dist_;
};

#endif // POINTOFCOMMONCOUPLING_H
