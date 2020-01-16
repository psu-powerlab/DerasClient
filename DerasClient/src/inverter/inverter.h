#ifndef INVERTER_H
#define INVERTER_H

#include "inverter.h"
#include "../utility/clock.h"
#include "../utility/entity.h"
#include "../battery/battery.h"
#include "../power/pointofcommoncoupling.h"

class Inverter;

// STATE PATTERN
// - this is the interface for all control states
class InverterState {
public:
    virtual ~InverterState ();
    virtual InverterState* Transition (Inverter& Inverter) = 0;
};

class IdleState : public InverterState {
public:
    IdleState ();
    InverterState* Transition (Inverter& Inverter);
};

// Super State
// - can be constant current/voltage sub-states
class PState : public InverterState
{
public:
    PState ();
    InverterState* Transition (Inverter& Inverter);
    void SetWatts ();

private:
    long int watts_;
};

// Sub States
class IdleP : public PState
{
public:
    IdleP ();
    InverterState* Transition (Inverter& Inverter);
};

class StartP : public PState
{
public:
    StartP ();
    InverterState* Transition (Inverter& Inverter);
};

class ActiveP : public PState
{
public:
    ActiveP ();
    InverterState* Transition (Inverter& Inverter);
};

class StopP : public PState
{
public:
    StopP ();
    InverterState* Transition (Inverter& Inverter);
};

class WarningP : public PState
{
public:
    WarningP ();
    InverterState* Transition (Inverter& Inverter);
};

class FaultP : public PState
{
public:
    FaultP ();
    InverterState* Transition (Inverter& Inverter);
};

// Super State
// - can be constant current/voltage sub-states
class QState : public InverterState
{
public:
    QState ();
    InverterState* Transition (Inverter& Inverter);
    void SetVARs ();

private:
    long int vars_;
};

// Sub States
class IdleQ : public QState
{
public:
    IdleQ ();
    InverterState* Transition (Inverter& Inverter);
};

class StartQ : public QState
{
public:
    StartQ ();
    InverterState* Transition (Inverter& Inverter);
};

class ActiveQ : public QState
{
public:
    ActiveQ ();
    InverterState* Transition (Inverter& Inverter);
};

class StopQ : public QState
{
public:
    StopQ ();
    InverterState* Transition (Inverter& Inverter);
};

class WarningQ : public QState
{
public:
    WarningQ ();
    InverterState* Transition (Inverter& Inverter);
};

class FaultQ : public QState
{
public:
    FaultQ ();
    InverterState* Transition (Inverter& Inverter);
};

// Inverter Simulator
class Inverter : public Entity
{
public:
    InverterModel* nameplate_;

public:
    Inverter
        (InverterModel* model, Battery* battery, PointOfCommonCoupling* pcc);
    virtual ~Inverter ();
    void Update ();
    void SetP (long int watts);
    void SetQ (long int vars);
    float GetVoltageAC ();
    float GetCurrentAC ();
    float GetActivePower ();
    float GetReactivePower ();
    float GetApparentPower ();
    float GetPowerFactor ();
    float GetImportEnergy ();
    float GetExportEnergy ();
    float GetGridVoltage ();
    float GetGridFrequency ();
    float GetBatteryVoltage ();
    float GetBatteryCurrent ();
    float GetBatterySOC ();

private:
    // concurrent states
    InverterState* active_state_;
    InverterState* reactive_state_;

    Clock* entity_clock_;
    Battery* battery_;
    PointOfCommonCoupling* pcc_;
    unsigned long long int last_update_;
    float current_ac_;
    float voltage_ac_;
    float active_power_;
    float reactive_power_;
    float apparent_power_;
    float power_factor_;

private:
    void SetState (InverterState* state);
};

#endif // INVERTER_H
