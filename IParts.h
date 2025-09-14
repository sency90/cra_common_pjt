#pragma once
#include <string>
#define interface struct
interface IParts{
public:
    virtual const std::string GetName() const=0;
    virtual ~IParts()=default;
};
