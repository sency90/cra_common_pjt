#pragma once
#include <string>
#include <stdexcept>
#define interface struct

interface ICarType{
public:
    virtual const std::string GetName() const=0;
};

class SedanCarType: public ICarType {
public:
    const std::string GetName() const override;
};

class SuvCarType: public ICarType {
public:
    const std::string GetName() const override;
};

class TruckCarType: public ICarType {
public:
    const std::string GetName() const override;
};

class UnknownCarType: public ICarType {
public:
    const std::string GetName() const override;
};



