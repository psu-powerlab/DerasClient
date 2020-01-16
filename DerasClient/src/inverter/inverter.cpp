#include "inverter.h"

InverterState::~InverterState()
{
    // do nothing
}

InverterState* InverterState::Transition(Inverter& Inverter)
{

}

InverterState* IdleState::Transition(Inverter& Inverter)
{

}

PState::PState()
{

}

InverterState* PState::Transition(Inverter& Inverter)
{

}

float PState::EmbodiedEnergy(Inverter& Inverter)
{

}

void PState::Voltage(Inverter& Inverter)
{

}

void PState::Current(Inverter& Inverter)
{

}

IdleP::IdleP()
{

}

InverterState* IdleP::Transition(Inverter& Inverter)
{

}

StartP::StartP()
{

}

InverterState* StartP::Transition(Inverter& Inverter)
{

}

ActiveP::ActiveP()
{

}

InverterState* ActiveP::Transition(Inverter& Inverter)
{

}

StopP::StopP()
{

}

InverterState* StopP::Transition(Inverter& Inverter)
{

}

WarningP::WarningP()
{

}

InverterState* WarningP::Transition(Inverter& Inverter)
{

}

FaultP::FaultP()
{

}

InverterState* FaultP::Transition(Inverter& Inverter)
{

}

QState::QState()
{

}

InverterState* QState::Transition(Inverter& Inverter)
{

}

float QState::EmbodiedEnergy(Inverter& Inverter)
{

}

void QState::Voltage(Inverter& Inverter)
{

}

void QState::Current(Inverter& Inverter)
{

}

IdleQ::IdleQ()
{

}

InverterState* IdleQ::Transition(Inverter& Inverter)
{

}

StartQ::StartQ()
{

}

InverterState* StartQ::Transition(Inverter& Inverter)
{

}

ActiveQ::ActiveQ()
{

}

InverterState* ActiveQ::Transition(Inverter& Inverter)
{

}

StopQ::StopQ()
{

}

InverterState* StopQ::Transition(Inverter& Inverter)
{

}

WarningQ::WarningQ()
{

}

InverterState* WarningQ::Transition(Inverter& Inverter)
{

}

FaultQ::FaultQ()
{

}

InverterState* FaultQ::Transition(Inverter& Inverter)
{

}

Inverter::Inverter(InverterModel* model, Battery* battery, PointOfCommonCoupling* pcc)
{

}

Inverter::~Inverter()
{

}

void Inverter::Update()
{

}

void Inverter::SetP(long int watts)
{

}

void Inverter::SetQ(long int vars)
{

}

float Inverter::GetVoltageAC()
{

}

float Inverter::GetCurrentAC()
{

}

float Inverter::GetActivePower()
{

}

float Inverter::GetReactivePower()
{

}

float Inverter::GetApparentPower()
{

}

float Inverter::GetPowerFactor()
{

}

float Inverter::GetImportEnergy()
{

}

float Inverter::GetExportEnergy()
{

}

float Inverter::GetGridVoltage()
{

}

float Inverter::GetGridFrequency()
{

}

float Inverter::GetBatteryVoltage()
{

}

float Inverter::GetBatteryCurrent()
{

}

float Inverter::GetBatterySOC()
{

}

void Inverter::SetState(InverterState* state)
{

}
