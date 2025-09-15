#pragma once
#include <cstdio>
#include <string>
#include "IParts.h"

struct ICarType: public IParts {
    virtual const std::string GetName() const=0;
    void Print() const override {
        printf("Car Type : %s\n", GetName().c_str());
    }
    virtual ~ICarType()=default;
};

class SedanCarType: public ICarType {
public:
    const std::string GetName() const override;
    virtual ~SedanCarType()=default;
};

class SuvCarType: public ICarType {
public:
    const std::string GetName() const override;
    virtual ~SuvCarType() = default;
};

class TruckCarType: public ICarType {
public:
    const std::string GetName() const override;
    virtual ~TruckCarType() = default;
};

class UnknownCarType: public ICarType {
public:
    const std::string GetName() const override;
    virtual ~UnknownCarType() = default;
};



