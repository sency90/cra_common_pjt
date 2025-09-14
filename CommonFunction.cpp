#include "CommonFunction.h"
#include <cctype>

CommonFunction &CommonFunction::GetInstance() {
    static CommonFunction cf;
    return cf;
}

std::string CommonFunction::ToLower(const std::string &s) {
    std::string ret;
    for(char c : s) {
        if(isupper(c)) ret += c-'A'+'a';
        else ret += c;
    }
    return ret;
}

bool CommonFunction::EqualsIgnoreCase(const std::string &s1, const std::string &s2) {
    std::string lower_s1 = ToLower(s1);
    std::string lower_s2 = ToLower(s2);
    return lower_s1 == lower_s2;
}
