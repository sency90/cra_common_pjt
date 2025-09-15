#pragma once
#include <cstdio>
#include <string>
#include "IParts.h"

struct IBrakeType: public IParts {
    virtual const std::string GetName() const=0;
    void Print() const override {
        printf("Brake System : %s\n", GetName().c_str());
    }
    virtual ~IBrakeType()=default;
};

class MandoBrakeType: public IBrakeType {
public:
    const std::string GetName() const override;
    virtual ~MandoBrakeType()=default;
};

class ContinentalBrakeType: public IBrakeType {
public:
    const std::string GetName() const override;
    virtual ~ContinentalBrakeType()=default;
};

class BoschBrakeType: public IBrakeType {
public:
    const std::string GetName() const override;
    virtual ~BoschBrakeType()=default;
};

class UnknownBrakeType: public IBrakeType {
public:
    const std::string GetName() const override;
    virtual ~UnknownBrakeType()=default;
};
