#pragma once
#include <cstdio>
#include <string>
#include "IParts.h"

struct ISteeringType: public IParts {
    virtual const std::string GetName() const=0;
    void Print() const override {
        printf("Steering System : %s\n", GetName().c_str());
    }
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
