#include <string>
#include "battery.h"

BatteryState::~BatteryState()
{
    // do nothing
}

IdleState::IdleState()
{
    // do nothing
}

BatteryState* IdleState::Transition(Battery& battery)
{
    if (battery.GetCurrent() > 0)
    {
        return new ChargingState ();
    }
    else if (battery.GetCurrent() < 0)
    {
        return new DischargingState ();
    }
    else
    {
        return NULL;
    }
}

ChargingState::ChargingState()
{
    // do nothing
}

float ChargingState::EmbodiedEnergy(Battery& battery)
{
    float i_now = battery.GetCurrent();
    float i_rtd = battery.nameplate_->current_rated_;
    float e_min = battery.nameplate_->charge_energy_min_;
    float e_max = battery.nameplate_->charge_energy_max_;
    return (i_now*(e_min - e_max)/i_rtd + e_max);
}

void ChargingState::Voltage(Battery& battery)
{
    float v_nom = battery.nameplate_->voltage_nominal_;
    float v_max = battery.nameplate_->voltage_max_;
    float e_max = battery.nameplate_->charge_energy_max_;
    float e_now = battery.GetStateOfCharge()*e_max;
    float ee = ChargingState::EmbodiedEnergy(battery);
    battery.SetVoltage(e_now*(v_max - v_nom)/ee + v_nom);
}

void ChargingState::Current(Battery& battery)
{
    float i_rtd = battery.nameplate_->current_rated_;
    float e_min = battery.nameplate_->charge_energy_min_;
    float e_max = battery.nameplate_->charge_energy_max_;
    float e_now = battery.GetStateOfCharge()*e_max;
    battery.SetCurrent(i_rtd*(e_now - e_max)/(e_min - e_max));
}

BatteryState* ChargingState::Transition(Battery& battery)
{
    // update voltage first and if it is at max then transition to const. volt
    ChargingState::Voltage(battery);
    if (battery.GetVoltage() == battery.nameplate_->voltage_max_)
    {
        ChargingState::Current(battery);
        return new ConstantVoltageCharging ();
    }
    else
    {
        return new ConstantCurrentCharging ();
    }
}

ConstantCurrentCharging::ConstantCurrentCharging()
{
    // do nothing
}

BatteryState* ConstantCurrentCharging::Transition(Battery& battery)
{
    // if the current is zero then there is no need to update any values
    if (battery.GetCurrent() == 0)
    {
        return new IdleState ();
    }
    // update voltage first and if it is at max then transition to const. volt
    ChargingState::Voltage(battery);
    if (battery.GetVoltage() == battery.nameplate_->voltage_max_)
    {
        ChargingState::Current(battery);
        return new ConstantVoltageCharging ();
    }
    else
    {
        return NULL;
    }
}

ConstantVoltageCharging::ConstantVoltageCharging()
{
    // do nothing
}

BatteryState* ConstantVoltageCharging::Transition(Battery& battery)
{
    // if the current is zero then there is no need to update any values
    if (battery.GetCurrent() == 0)
    {
        return new IdleState ();
    }

    // no checks other than if the current has reached zero from this state
    ChargingState::Current(battery);
    return NULL;
}

DischargingState::DischargingState()
{
    // do nothing
}

float DischargingState::EmbodiedEnergy(Battery& battery)
{
    float i_now = -battery.GetCurrent();
    float i_rtd = battery.nameplate_->current_rated_;
    float e_min = battery.nameplate_->discharge_energy_min_;
    float e_max = battery.nameplate_->discharge_energy_max_;
    return (i_now*(e_min - e_max)/i_rtd + e_max);
}

void DischargingState::Voltage(Battery& battery)
{
    float v_min = battery.nameplate_->voltage_min_;
    float v_max = battery.nameplate_->voltage_max_;
    float e_max = battery.nameplate_->discharge_energy_max_;
    float e_now = (e_max - battery.GetStateOfCharge()*e_max);
    float ee = DischargingState::EmbodiedEnergy(battery);
    battery.SetVoltage(e_now*(v_min - v_max)/ee + v_max);
}

void DischargingState::Current(Battery& battery)
{
    float i_rtd = battery.nameplate_->current_rated_;
    float e_min = battery.nameplate_->discharge_energy_min_;
    float e_max = battery.nameplate_->discharge_energy_max_;
    float e_now = (e_max - battery.GetStateOfCharge()*e_max);
    float current = -i_rtd*(e_now - e_max)/(e_min - e_max);
    battery.SetCurrent(current);
}

BatteryState* DischargingState::Transition(Battery& battery)
{
    // update voltage first and if it is at min then transition to const. volt
    DischargingState::Voltage(battery);
    if (battery.GetVoltage() == battery.nameplate_->voltage_min_)
    {
        DischargingState::Current(battery);
        return new ConstantVoltageDischarging ();
    }
    else
    {
        return new ConstantCurrentDischarging ();
    }
}

ConstantCurrentDischarging::ConstantCurrentDischarging()
{
    // do nothing
}

BatteryState* ConstantCurrentDischarging::Transition(Battery& battery)
{
    // if the current is zero then there is no need to update any values
    if (battery.GetCurrent() == 0)
    {
        return new IdleState ();
    }

    // update voltage first and if it is at min then transition to const. volt
    DischargingState::Voltage(battery);
    if (battery.GetVoltage() == battery.nameplate_->voltage_min_)
    {
        DischargingState::Current(battery);
        return new ConstantVoltageDischarging ();
    }
    else
    {
        return NULL;
    }
}

ConstantVoltageDischarging::ConstantVoltageDischarging()
{
    // do nothing
}

BatteryState* ConstantVoltageDischarging::Transition(Battery& battery)
{
    // if the current is zero then there is no need to update any values
    if (battery.GetCurrent() == 0)
    {
        return new IdleState ();
    }

    // no checks other than if the current has reached zero from this state
    DischargingState::Current(battery);
    return NULL;
}

Battery::Battery(BatteryModel* model)
{
    std::cout << "[BATTERY]\n... constructed\n";
    state_ = new IdleState();
    entity_clock_ = Clock::Instance();
    nameplate_ = model;
    voltage_dc_ = nameplate_->voltage_nominal_;
    current_dc_ = 0;
    state_of_charge_ = 0.5;
    last_update_ = entity_clock_->GetUtc();
}

void Battery::Update()
{
    Battery::SetState(state_->Transition (*this));

    // find elapsed time
    unsigned long long int utc = entity_clock_->GetUtc();
    unsigned int dt =  utc - last_update_;
    last_update_ = utc;

    // update soc base on state
    float power_dc = voltage_dc_*current_dc_;
    if (power_dc > 0)
    {
        float e = state_of_charge_*nameplate_->charge_energy_max_;
        float e_dt = power_dc * dt/3600;
        float soc = (e+e_dt)/nameplate_->charge_energy_max_;
        Battery::SetStateOfCharge(soc);
    }
    else
    {
        float e = state_of_charge_*nameplate_->discharge_energy_max_;
        float e_dt = power_dc * dt/3600;
        float soc = (e+e_dt)/nameplate_->discharge_energy_max_;
        Battery::SetStateOfCharge(soc);
    }
}

void Battery::SetState(BatteryState* state)
{
    if (state != NULL) {
        delete state_;
        state_ = state;
    }
}

void Battery::SetCurrent(float current)
{
    float current_rated = nameplate_->current_rated_;
    if (current > current_rated)
    {
        current_dc_ = current_rated;
    }
    else if (current < -current_rated)
    {
        current_dc_ = -current_rated;
    }
    else
    {
        current_dc_ = current;
    }
}

void Battery::SetVoltage(float voltage)
{
    if (voltage > nameplate_->voltage_max_)
    {
        voltage_dc_ = nameplate_->voltage_max_;
    }
    else if (voltage < nameplate_->voltage_min_)
    {
        voltage_dc_ = nameplate_->voltage_min_;
    }
    else
    {
        voltage_dc_ = voltage;
    }
}

void Battery::SetStateOfCharge(float soc)
{
    if (soc > 1)
    {
        state_of_charge_ = 1;
    }
    else if (soc < 0)
    {
        state_of_charge_ = 0;
    }
    else
    {
        state_of_charge_ = soc;
    }
}

float Battery::GetVoltage()
{
    return voltage_dc_;
}

float Battery::GetCurrent()
{
    return current_dc_;
}

float Battery::GetStateOfCharge()
{
    return state_of_charge_;
}
