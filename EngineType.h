#pragma once
#include <cstdio>
#include <string>
#include "IParts.h"

struct IEngineType: public IParts {
    virtual const std::string GetName() const =0;
    void Print() const override {
        printf("Engine : %s\n", GetName().c_str());
    }
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
