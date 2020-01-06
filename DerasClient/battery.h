#ifndef BATTERY_H
#define BATTERY_H

#include "clock.h"
#include "entity.h"
#include "batterymodel.h"

class Battery;

// STATE PATTERN
// - this is the interface for all control states
class BatteryState {
public:
    virtual ~BatteryState ();
    virtual BatteryState* Transition (Battery& battery) = 0;
};

class IdleState : public BatteryState {
public:
    IdleState ();
    BatteryState* Transition (Battery& battery);
};

// Super State
// - can be constant current/voltage sub-states
class ChargingState : public BatteryState
{
public:
    ChargingState ();
    BatteryState* Transition (Battery& battery);
    float EmbodiedEnergy (Battery& battery);
    void Voltage (Battery& battery);
    void Current (Battery& battery);
};

// Sub States
class ConstantCurrentCharging : public ChargingState
{
public:
    ConstantCurrentCharging ();
    BatteryState* Transition (Battery& battery);
};

class ConstantVoltageCharging : public ChargingState
{
public:
    ConstantVoltageCharging ();
    BatteryState* Transition (Battery& battery);
};

// Super State
// - can be constant current/voltage sub-states
class DischargingState : public BatteryState
{
public:
    DischargingState ();
    BatteryState* Transition(Battery& battery);
    float EmbodiedEnergy (Battery& battery);
    void Voltage (Battery& battery);
    void Current (Battery& battery);
};

// Sub States
class ConstantCurrentDischarging : public DischargingState
{
public:
    ConstantCurrentDischarging ();
    BatteryState* Transition (Battery& battery);
};

class ConstantVoltageDischarging : public DischargingState
{
public:
    ConstantVoltageDischarging ();
    BatteryState* Transition (Battery& battery);
};

// Battery Simulator
class Battery : public Entity
{
public:
    BatteryModel* nameplate_;

public:
    Battery (BatteryModel* model);
    virtual ~Battery () {};
    void Update ();
    void SetCurrent (float current);
    void SetVoltage (float voltage);
    void SetStateOfCharge (float soc);
    float GetVoltage ();
    float GetCurrent ();
    float GetStateOfCharge ();

private:
    BatteryState* state_;
    Clock* entity_clock_;
    unsigned long long int last_update_;
    float current_dc_;
    float voltage_dc_;
    float state_of_charge_;

private:
    void SetState (BatteryState* state);
};

#endif // BATTERY_H
