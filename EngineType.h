#pragma once
#include <string>

#define interface struct
interface IEngineType{
public:
    virtual const std::string GetName() const =0;
};
class GmEngineType: public IEngineType {
public:
    const std::string GetName() const override;
};

class ToyotaEngineType: public IEngineType {
public:
    const std::string GetName() const override;
};

class WiaEngineType: public IEngineType {
public:
    const std::string GetName() const override;
};

class BrokenEngineType: public IEngineType {
public:
    const std::string GetName() const override;
};

class UnknownEngineType: public IEngineType {
public:
    const std::string GetName() const override;
};
