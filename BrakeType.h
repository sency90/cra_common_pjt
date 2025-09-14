#pragma once
#define interface struct
#include <string>

interface IBrakeType{
    virtual const std::string GetName() const=0;
};

class MandoBrakeType: public IBrakeType {
public:
    const std::string GetName() const override;
};

class ContinentalBrakeType: public IBrakeType {
public:
    const std::string GetName() const override;
};

class BoschBrakeType: public IBrakeType {
public:
    const std::string GetName() const override;
};

class UnknownBrakeType: public IBrakeType {
public:
    const std::string GetName() const override;
};
