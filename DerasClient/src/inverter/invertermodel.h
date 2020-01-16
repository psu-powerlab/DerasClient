#ifndef INVERTERMODEL_H_INCLUDED
#define INVERTERMODEL_H_INCLUDED

// pure abstract
class InverterModel
{
public:
    InverterModel (
        unsigned int volts_ac,
        unsigned int amps_ac,
        unsigned int hertz,
        unsigned int max_volts_dc,
        unsigned int min_volts_dc,
        unsigned int amps_dc,
        std::string type)
    :
        rated_volts_ac_(volts_ac),
        rated_amps_ac_(amps_ac),
        rated_hertz_(hertz),
        rated_amps_dc_(max_volts_dc),
        max_volts_dc_(min_volts_dc),
        min_volts_dc_(amps_dc),
        type_(type) {};

    const unsigned int rated_volts_ac_;
    const unsigned int rated_amps_ac_;
    const unsigned int rated_hertz_;
    const unsigned int rated_amps_dc_;
    const unsigned int max_volts_dc_;
    const unsigned int min_volts_dc_;
    const std::string type_;
};

#endif // INVERTERMODEL_H_INCLUDED
