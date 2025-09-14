#pragma once
#include <string>
#include "IParts.h"
#define interface struct

interface IBrakeType: public IParts{
public:
    virtual const std::string GetName() const=0;
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
