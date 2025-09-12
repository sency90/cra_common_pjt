#pragma execution_character_set("utf-8")
#include <windows.h>

#ifdef _DEBUG
#include "gmock/gmock.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stdexcept>

#define CLEAR_SCREEN "\033[H\033[2J"

namespace {
    constexpr int NA = -1;
};

int stack[10];

void SelectCarType(int answer);
void SelectEngine(int answer);
void SelectbrakeSystem(int answer);
void SelectSteeringSystem(int answer);
void RunProducedCar();
void TestProducedCar();
void delay(int ms);

enum QuestionType {
    CarType_Q,
    Engine_Q,
    BrakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

enum CarType {
    SEDAN = 1,
    SUV,
    TRUCK
};

enum Engine {
    GM = 1,
    TOYOTA,
    WIA
};

enum brakeSystem {
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};

enum SteeringSystem {
    BOSCH_S = 1,
    MOBIS
};

void delay(int ms) {
    Sleep(ms);
}

inline void PrintChoiceCarTypePage() {
    printf(CLEAR_SCREEN);
    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
    printf("어떤 차량 타입을 선택할까요?\n");
    printf("1. Sedan\n");
    printf("2. SUV\n");
    printf("3. Truck\n");
}

inline void PrintChoiceEngineTypePage() {
    printf(CLEAR_SCREEN);
    printf("어떤 엔진을 탑재할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. 고장난 엔진\n");
}

inline void PrintChoiceBrakeTypePage() {
    printf(CLEAR_SCREEN);
    printf("어떤 제동장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
}

inline void PrintChoiceSteeringTypePage() {
    printf(CLEAR_SCREEN);
    printf("어떤 조향장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
}

inline void PrintChoiceRunAndTestPage() {
    printf(CLEAR_SCREEN);
    printf("멋진 차량이 완성되었습니다.\n");
    printf("어떤 동작을 할까요?\n");
    printf("0. 처음 화면으로 돌아가기\n");
    printf("1. RUN\n");
    printf("2. Test\n");
}

inline void PrintChoicePage(int step) {
    if(step == CarType_Q) {
        PrintChoiceCarTypePage();
    }
    else if(step == Engine_Q) {
        PrintChoiceEngineTypePage();
    }
    else if(step == BrakeSystem_Q) {
        PrintChoiceBrakeTypePage();
    }
    else if(step == SteeringSystem_Q) {
        PrintChoiceSteeringTypePage();
    }
    else if(step == Run_Test) {
        PrintChoiceRunAndTestPage();
    }
}

bool WhenSelectGoFirstPage(int answer, int step) {
    return answer == 0 && step == Run_Test;
}

bool WhenSelectGoPreviousPage(int answer, int step) {
    return answer == 0 && step >= 1;
}

bool WhenTypedExit(char *input) {
    return strcmp(input, "exit")==0;
}

void ExitProgram() {
    printf("바이바이\n");
    exit(0);
}

void GetInput(char *input) {
    printf("===============================\n");

    printf("INPUT > ");
    fgets(input, sizeof(input), stdin);

}

void RemoveEndNewLine(char *input) {
    // 엔터 개행문자 제거
    char *context = nullptr;
    strtok_s(input, "\r", &context);
    strtok_s(input, "\n", &context);
}

void ValidateInput(char *input, int step) {
    // 숫자로 된 대답인지 확인
    char *checkNumber;
    int answer = strtol(input, &checkNumber, 10); // 문자열을 10진수로 변환

    // 입력받은 문자가 숫자가 아니라면
    if(*checkNumber != '\0') {
        throw std::invalid_argument("숫자만 입력 가능");
    }

    if(step == CarType_Q && !(answer >= 1 && answer <= 3)) {
        throw std::invalid_argument("차량 타입은 1 ~ 3 범위만 선택 가능");
    }

    if(step == Engine_Q && !(answer >= 0 && answer <= 4)) {
        throw std::invalid_argument("엔진은 1 ~ 4 범위만 선택 가능");
    }

    if(step == BrakeSystem_Q && !(answer >= 0 && answer <= 3)) {
        throw std::invalid_argument("제동장치는 1 ~ 3 범위만 선택 가능");
    }

    if(step == SteeringSystem_Q && !(answer >= 0 && answer <= 2)) {
        throw std::invalid_argument("조향장치는 1 ~ 2 범위만 선택 가능");
    }

    if(step == Run_Test && !(answer >= 0 && answer <= 2)) {
        throw std::invalid_argument("Run 또는 Test 중 하나를 선택 필요");
    }
}

//ValidateInput()다음에 ChangeInputTypeToInt()가 실행되어야 한다.
int ChangeInputTypeToInt(char *input) noexcept {
    char *checkNumber;
    int answer = strtol(input, &checkNumber, 10); // 문자열을 10진수로 변환
    return answer;
}

void SelectNextPage(int answer, int &step) {
    // 처음으로 돌아가기
    if(WhenSelectGoFirstPage(answer, step)) {
        step = CarType_Q;
        return;
    }

    // 이전으로 돌아가기
    if(WhenSelectGoPreviousPage(answer, step)) {
        step -= 1;
        return;
    }

    if(step == CarType_Q) {
        SelectCarType(answer);
        delay(800);
        step = Engine_Q;
    }
    else if(step == Engine_Q) {
        SelectEngine(answer);
        delay(800);
        step = BrakeSystem_Q;
    }
    else if(step == BrakeSystem_Q) {
        SelectbrakeSystem(answer);
        delay(800);
        step = SteeringSystem_Q;
    }
    else if(step == SteeringSystem_Q) {
        SelectSteeringSystem(answer);
        delay(800);
        step = Run_Test;
    }
    else if(step == Run_Test && answer == 1) {
        RunProducedCar();
        delay(2000);
    }
    else if(step == Run_Test && answer == 2) {
        printf("Test...\n");
        delay(1500);
        TestProducedCar();
        delay(2000);
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    char input[100];
    int step = CarType_Q;

    while(1) {
        PrintChoicePage(step);

        GetInput(input);
        RemoveEndNewLine(input);

        if(WhenTypedExit(input)) {
            ExitProgram();
        }

        try {
            ValidateInput(input, step);
        }
        catch(std::exception &ex) {
            printf("ERROR :: %s\n", ex.what());
            delay(800);
            continue;
        }

        int answer = ChangeInputTypeToInt(input);
        SelectNextPage(answer, step);
    }

    return 0;
}

void SelectCarType(int answer) {
    stack[CarType_Q] = answer;
    if(answer == 1)
        printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
    if(answer == 2)
        printf("차량 타입으로 SUV을 선택하셨습니다.\n");
    if(answer == 3)
        printf("차량 타입으로 Truck을 선택하셨습니다.\n");
}

void SelectEngine(int answer) {
    stack[Engine_Q] = answer;
    if(answer == 1)
        printf("GM 엔진을 선택하셨습니다.\n");
    if(answer == 2)
        printf("TOYOTA 엔진을 선택하셨습니다.\n");
    if(answer == 3)
        printf("WIA 엔진을 선택하셨습니다.\n");
}

void SelectbrakeSystem(int answer) {
    stack[BrakeSystem_Q] = answer;
    if(answer == 1)
        printf("MANDO 제동장치를 선택하셨습니다.\n");
    if(answer == 2)
        printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
    if(answer == 3)
        printf("BOSCH 제동장치를 선택하셨습니다.\n");
}

void SelectSteeringSystem(int answer) {
    stack[SteeringSystem_Q] = answer;
    if(answer == 1)
        printf("BOSCH 조향장치를 선택하셨습니다.\n");
    if(answer == 2)
        printf("MOBIS 조향장치를 선택하셨습니다.\n");
}

int IsValidCheck() {
    if(stack[CarType_Q] == SEDAN && stack[BrakeSystem_Q] == CONTINENTAL) {
        return false;
    }
    else if(stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA) {
        return false;
    }
    else if(stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA) {
        return false;
    }
    else if(stack[CarType_Q] == TRUCK && stack[BrakeSystem_Q] == MANDO) {
        return false;
    }
    else if(stack[BrakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S) {
        return false;
    }

    return true;
}

void PrintAssembledCarType() {
    static const char *car_type[3] = {"Sedan", "SUV", "Truck"};
    printf("Car Type : %s\n", car_type[stack[CarType_Q]-1]);
}

void PrintAssembledCarEngineType() {
    static const char *engine_type[3] = {"GM", "TOYOTA", "WIA"};
    printf("Engine : %s\n", engine_type[stack[Engine_Q]-1]);
}

void PrintAssembeldCarBrakeType() {
    static const char *brake_type[3] = {"Mando", "Continental", "Bosch"};
    printf("Brake System : %s\n", brake_type[stack[BrakeSystem_Q]-1]);
}
void PrintAssembledCarSteeringType() {
    static const char *steering_type[2] = { "Bosch", "Mobis" };
    printf("SteeringSystem : %s\n", steering_type[stack[SteeringSystem_Q]-1]);
}

void RunProducedCar() {
    if(IsValidCheck() == false) {
        printf("자동차가 동작되지 않습니다\n");
        return;
    }

    if(stack[Engine_Q] == 4) {
        printf("엔진이 고장나있습니다.\n");
        printf("자동차가 움직이지 않습니다.\n");
        return;
    }

    PrintAssembledCarType();
    PrintAssembledCarEngineType();
    PrintAssembeldCarBrakeType();
    PrintAssembledCarSteeringType();

    printf("자동차가 동작됩니다.\n");
}

void TestProducedCar() {
    if(stack[CarType_Q] == SEDAN && stack[BrakeSystem_Q] == CONTINENTAL) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
    }
    else if(stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
    }
    else if(stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
    }
    else if(stack[CarType_Q] == TRUCK && stack[BrakeSystem_Q] == MANDO) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
    }
    else if(stack[BrakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
    }
    else {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
    }
}
#endif