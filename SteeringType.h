#pragma once
#define interface struct
#include <string>

interface ISteeringType{
public:
    virtual const std::string GetName() const=0;
};

class BoschSteeringType: public ISteeringType {
public:
    const std::string GetName() const override;
};

class MobisSteeringType: public ISteeringType {
public:
    const std::string GetName() const override;
};

class UnknownSteeringType: public ISteeringType {
public:
    const std::string GetName() const override;
};
