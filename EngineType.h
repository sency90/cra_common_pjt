#pragma once
#include <string>
#include "IParts.h"

#define interface struct
interface IEngineType : public IParts{
public:
    virtual const std::string GetName() const =0;
    virtual ~IEngineType() = default;
};
class GmEngineType: public IEngineType {
public:
    const std::string GetName() const override;
    virtual ~GmEngineType() = default;
};

class ToyotaEngineType: public IEngineType {
public:
    const std::string GetName() const override;
    virtual ~ToyotaEngineType() = default;
};

class WiaEngineType: public IEngineType {
public:
    const std::string GetName() const override;
    virtual ~WiaEngineType() = default;
};

class BrokenEngineType: public IEngineType {
public:
    const std::string GetName() const override;
    virtual ~BrokenEngineType() = default;
};

class UnknownEngineType: public IEngineType {
public:
    const std::string GetName() const override;
    virtual ~UnknownEngineType() = default;
};
