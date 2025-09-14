#pragma once
#include <string>
#include <stdexcept>
#include "IParts.h"
#define interface struct

interface ICarType : public IParts{
public:
    virtual const std::string GetName() const=0;
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



