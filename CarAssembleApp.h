#pragma once
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <chrono>
#include <thread>

#include "Enum.h"

#ifdef _WIN32
#pragma execution_character_set("utf-8")
#include <windows.h>
#endif

#define CLEAR_SCREEN "\033[H\033[2J"

class CarAssembleApp {
public:
    int settings[10];
    const char *car_type[4] = { "None", "Sedan", "SUV", "Truck" };
    const char *engine_type[4] = { "None", "GM", "TOYOTA", "WIA" };
    const char *brake_type[4] = { "None", "Mando", "Continental", "Bosch" };
    const char *steering_type[3] = { "None", "Bosch", "Mobis" };

    CarAssembleApp() {
#ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
#endif

        memset(settings, 0, sizeof(settings));
    }

public:
    void Delay(int ms) {
#if _DEBUG
        std::this_thread::sleep_for(std::chrono::milliseconds(ms/10));
#else
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
#endif
    }

    void PrintChoiceCarTypePage() {
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

    void PrintChoiceEngineTypePage() {
        printf("어떤 엔진을 탑재할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. GM\n");
        printf("2. TOYOTA\n");
        printf("3. WIA\n");
        printf("4. 고장난 엔진\n");
    }

    void PrintChoiceBrakeTypePage() {
        printf("어떤 제동장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. MANDO\n");
        printf("2. CONTINENTAL\n");
        printf("3. BOSCH\n");
    }

    void PrintChoiceSteeringTypePage() {
        printf("어떤 조향장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. BOSCH\n");
        printf("2. MOBIS\n");
    }

    void PrintChoiceRunAndTestPage() {
        printf("멋진 차량이 완성되었습니다.\n");
        printf("어떤 동작을 할까요?\n");
        printf("0. 처음 화면으로 돌아가기\n");
        printf("1. RUN\n");
        printf("2. Test\n");
    }

    void PrintChoicePage(int page) {
        printf(CLEAR_SCREEN);

        if(page == eCarTypePage) {
            PrintChoiceCarTypePage();
        }
        else if(page == eEnginePage) {
            PrintChoiceEngineTypePage();
        }
        else if(page == eBrakePage) {
            PrintChoiceBrakeTypePage();
        }
        else if(page == eSteeringPage) {
            PrintChoiceSteeringTypePage();
        }
        else if(page == eRunOrTestPage) {
            PrintChoiceRunAndTestPage();
        }

        printf("===============================\n");
    }

    bool WhenTypedExit(char *input) {
        return strcmp(input, "exit")==0;
    }

    void ExitProgram() {
        printf("바이바이\n");
        exit(0);
    }

    char *GetInput() {
        static char input[128];

        printf("INPUT > ");
        fgets(input, sizeof(input), stdin);
        return input;
    }

    void RemoveEndNewLine(char *input) {
        // 엔터 개행문자 제거
        char *context = nullptr;
        strtok_s(input, "\r", &context);
        strtok_s(input, "\n", &context);
    }

    void ValidateInput(const char *input, int page);

    //ValidateInput()다음에 ChangeInputTypeToInt()가 실행되어야 한다.
    int ChangeInputTypeToInt(char *input) noexcept {
        char *checkNumber;
        int answer = strtol(input, &checkNumber, 10); // 문자열을 10진수로 변환
        return answer;
    }

    bool IsStartPage(int page) {
        return page == eCarTypePage;
    }
    bool IsEndPage(int page) {
        return page == eRunOrTestPage;
    }

    bool IsSelectGoBackToStartPage(int answer, int page) {
        return answer==0 && IsEndPage(page);
    }

    bool IsSelectGoBackToPrevPage(int answer, int page) {
        return answer==0 && false==IsStartPage(page) && false==IsEndPage(page);
    }

    void SelectParts(int answer, int page) {
        switch(page) {
        case eCarTypePage: {
            SelectCarType(answer);
            Delay(800);
            break;
        }
        case eEnginePage: {
            SelectEngine(answer);
            Delay(800);
            break;
        }
        case eBrakePage: {
            SelectBrake(answer);
            Delay(800);
            break;
        }
        case eSteeringPage: {
            SelectSteering(answer);
            Delay(800);
            break;
        }
        case eRunOrTestPage: {
            if(answer == 1) {
                RunProducedCar();
            }
            else if(answer == 2) {
                printf("Test...\n");
                Delay(1500);
                TestProducedCar();
            }
            Delay(2000);
            break;
        }
        } //switch
    }

    int GetStartPage() {
        return eCarTypePage;
    }

    void SelectNextPage(int answer, int &page) {
        // 처음으로 돌아가기
        if(IsSelectGoBackToStartPage(answer, page)) {
            page = GetStartPage();
            return;
        }

        // 이전으로 돌아가기
        if(IsSelectGoBackToPrevPage(answer, page)) {
            page--;
            return;
        }

        if(false == IsEndPage(page)) {
            page++;
        }
    }


    int Run() {
        int current_page = GetStartPage();

        while(1) {
            PrintChoicePage(current_page);

            char *input = GetInput();
            RemoveEndNewLine(input);

            if(WhenTypedExit(input)) {
                ExitProgram();
            }

            try {
                ValidateInput(input, current_page);
            }
            catch(std::exception &ex) {
                printf("ERROR :: %s\n", ex.what());
                Delay(800);
                continue;
            }

            int answer = ChangeInputTypeToInt(input);
            SelectParts(answer, current_page);
            SelectNextPage(answer, current_page);
        }

        return 0;
    }

    void SelectCarType(int answer) {
        settings[eCarTypePage] = answer;
        if(answer == eSedanCar)
            printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
        if(answer == eSUVCar)
            printf("차량 타입으로 SUV을 선택하셨습니다.\n");
        if(answer == eTruckCar)
            printf("차량 타입으로 Truck을 선택하셨습니다.\n");
    }

    void SelectEngine(int answer) {
        settings[eEnginePage] = answer;
        if(answer == eGMEngine)
            printf("GM 엔진을 선택하셨습니다.\n");
        if(answer == eTOYOTAEngine)
            printf("TOYOTA 엔진을 선택하셨습니다.\n");
        if(answer == eWIAEngine)
            printf("WIA 엔진을 선택하셨습니다.\n");
    }

    void SelectBrake(int answer) {
        settings[eBrakePage] = answer;
        if(answer == eMANDOBrake)
            printf("MANDO 제동장치를 선택하셨습니다.\n");
        if(answer == eCONTINENTALBrake)
            printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
        if(answer == eBOSCHBrake)
            printf("BOSCH 제동장치를 선택하셨습니다.\n");
    }

    void SelectSteering(int answer) {
        settings[eSteeringPage] = answer;
        if(answer == eBOSCHSteering)
            printf("BOSCH 조향장치를 선택하셨습니다.\n");
        if(answer == eMOBISSteering)
            printf("MOBIS 조향장치를 선택하셨습니다.\n");
    }


    const char *CurrentCarTypeSettingToString() {
        return car_type[settings[eCarTypePage]];
    }
    const char *CurrentEngineSettingToString() {
        return engine_type[settings[eEnginePage]];
    }
    const char *CurrentBrakeSettingToString() {
        return brake_type[settings[eBrakePage]];
    }
    const char *CurrentSteeringSettingToString() {
        return steering_type[settings[eSteeringPage]];
    }

    int IsValidCheck() {
        if(settings[eCarTypePage] == eSedanCar && settings[eBrakePage] == eCONTINENTALBrake) {
            return false;
        }
        else if(settings[eCarTypePage] == eSUVCar && settings[eEnginePage] == eTOYOTAEngine) {
            return false;
        }
        else if(settings[eCarTypePage] == eTruckCar && settings[eEnginePage] == eWIAEngine) {
            return false;
        }
        else if(settings[eCarTypePage] == eTruckCar && settings[eBrakePage] == eMANDOBrake) {
            return false;
        }
        else if(settings[eBrakePage] == eBOSCHBrake && settings[eSteeringPage] != eBOSCHSteering) {
            return false;
        }

        return true;
    }

    void PrintAssembledCarType() {
        printf("Car Type : %s\n", CurrentCarTypeSettingToString());
    }

    void PrintAssembledCarEngineType() {
        printf("Engine : %s\n", CurrentEngineSettingToString());
    }

    void PrintAssembeldCarBrakeType() {
        printf("Brake System : %s\n", CurrentBrakeSettingToString());
    }

    void PrintAssembledCarSteeringType() {
        printf("SteeringSystem : %s\n", CurrentSteeringSettingToString());
    }

    void RunProducedCar() {
        if(IsValidCheck() == false) {
            printf("자동차가 동작되지 않습니다\n");
            return;
        }

        if(settings[eEnginePage] == eBrokenEngine) {
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
        if(settings[eCarTypePage] == eSedanCar && settings[eBrakePage] == eCONTINENTALBrake) {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Sedan에는 Continental제동장치 사용 불가\n");
        }
        else if(settings[eCarTypePage] == eSUVCar && settings[eEnginePage] == eTOYOTAEngine) {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("SUV에는 TOYOTA엔진 사용 불가\n");
        }
        else if(settings[eCarTypePage] == eTruckCar && settings[eEnginePage] == eWIAEngine) {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Truck에는 WIA엔진 사용 불가\n");
        }
        else if(settings[eCarTypePage] == eTruckCar && settings[eBrakePage] == eMANDOBrake) {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Truck에는 Mando제동장치 사용 불가\n");
        }
        else if(settings[eBrakePage] == eBOSCHBrake && settings[eSteeringPage] != eBOSCHSteering) {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
        }
        else {
            printf("자동차 부품 조합 테스트 결과 : PASS\n");
        }
    }
};
