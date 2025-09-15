#pragma once
#include <string>
#include <memory>
#include <utility>

template <typename T, typename D = std::default_delete<T>>
using up = std::unique_ptr<T, D>;

template <typename T, typename... Args>
inline up<T> make_up(Args&&... args) { 
    return std::make_unique<T>(std::forward<Args>(args)...);
}

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
