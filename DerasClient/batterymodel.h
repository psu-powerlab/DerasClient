#ifndef BATTERYMODEL_H
#define BATTERYMODEL_H

#include <iostream>
#include <string>

// pure abstract
class BatteryModel
{
public:
    BatteryModel (
        unsigned int vmin,
        unsigned int vmax,
        unsigned int vnom,
        unsigned int irtd,
        unsigned int ce_min,
        unsigned int ce_max,
        unsigned int de_min,
        unsigned int de_max,
        std::string type)
    :
        voltage_min_(vmin),
        voltage_max_(vmax),
        voltage_nominal_(vnom),
        current_rated_(irtd),
        charge_energy_min_(ce_min),
        charge_energy_max_(ce_max),
        discharge_energy_min_(de_min),
        discharge_energy_max_(de_max),
        type_(type) {};

    const unsigned int voltage_min_;
    const unsigned int voltage_max_;
    const unsigned int voltage_nominal_;
    const unsigned int current_rated_;
    const unsigned int charge_energy_min_;
    const unsigned int charge_energy_max_;
    const unsigned int discharge_energy_min_;
    const unsigned int discharge_energy_max_;
    const std::string type_;
};

#endif // BATTERYMODEL_H

