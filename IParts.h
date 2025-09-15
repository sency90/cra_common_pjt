#pragma once
#include <string>

struct IParts {
    virtual const std::string GetName() const=0;
    virtual void Print() const=0;
    virtual ~IParts()=default;
};
