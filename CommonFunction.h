#pragma once
#include <string>

class CommonFunction {
private:
    CommonFunction()=default;

public:
    static CommonFunction &GetInstance();

public:
    std::string ToLower(const std::string &s);
    bool EqualsIgnoreCase(const std::string &s1, const std::string &s2);
    void PrintSettingForKorean();
};
