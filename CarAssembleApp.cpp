#include "CarAssembleApp.h"

void CarAssembleApp::ValidateInput(const char *input, int page) {
    // 숫자로 된 대답인지 확인
    char *checkNumber;
    int answer = strtol(input, &checkNumber, 10); // 문자열을 10진수로 변환

    // 입력받은 문자가 숫자가 아니라면
    if(*checkNumber != '\0') {
        throw std::invalid_argument("숫자만 입력 가능");
    }

    if(page == eCarTypePage && !(answer >= 1 && answer <= 3)) {
        throw std::invalid_argument("차량 타입은 1 ~ 3 범위만 선택 가능");
    }

    if(page == eEnginePage && !(answer >= 0 && answer <= 4)) {
        throw std::invalid_argument("엔진은 1 ~ 4 범위만 선택 가능");
    }

    if(page == eBrakePage && !(answer >= 0 && answer <= 3)) {
        throw std::invalid_argument("제동장치는 1 ~ 3 범위만 선택 가능");
    }

    if(page == eSteeringPage && !(answer >= 0 && answer <= 2)) {
        throw std::invalid_argument("조향장치는 1 ~ 2 범위만 선택 가능");
    }

    if(page == eRunOrTestPage && !(answer >= 0 && answer <= 2)) {
        throw std::invalid_argument("Run 또는 Test 중 하나를 선택 필요");
    }
}
