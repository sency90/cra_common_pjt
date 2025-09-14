#pragma once
#include <string>
#include "IParts.h"

#define interface struct
interface ISteeringType{
public:
    virtual const std::string GetName() const=0;
    virtual ~ISteeringType()=default;
};

class BoschSteeringType: public ISteeringType {
public:
    const std::string GetName() const override;
    virtual ~BoschSteeringType()=default;
};

class MobisSteeringType: public ISteeringType {
public:
    const std::string GetName() const override;
    virtual ~MobisSteeringType()=default;
};

class UnknownSteeringType: public ISteeringType {
public:
    const std::string GetName() const override;
    virtual ~UnknownSteeringType()=default;
};
