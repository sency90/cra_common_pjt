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

    CarAssembleApp();

public:
    void Delay(int ms) {
#if _DEBUG
        std::this_thread::sleep_for(std::chrono::milliseconds(ms/10));
#else
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
#endif
    }

    void PrintChoiceCarTypePage();
    void PrintChoiceEngineTypePage();
    void PrintChoiceBrakeTypePage();
    void PrintChoiceSteeringTypePage();
    void PrintChoiceRunAndTestPage();
    void PrintChoicePage(int page);

    bool WhenTypedExit(char *input);

    virtual void ExitProgram();

    virtual char *GetInput();

    void RemoveEndNewLine(char *input);

    void ValidateInput(const char *input, int page);

    //ValidateInput()다음에 ChangeInputTypeToInt()가 실행되어야 한다.
    int ChangeInputTypeToInt(char *input) noexcept;

    bool IsStartPage(int page);
    bool IsEndPage(int page);

    bool IsSelectGoBackToStartPage(int answer, int page);

    bool IsSelectGoBackToPrevPage(int answer, int page);

    void SelectParts(int answer, int page);

    int GetStartPage();

    void SelectNextPage(int answer, int &page);


    int Run();

    void SelectCarType(int answer);

    void SelectEngine(int answer);

    void SelectBrake(int answer);

    void SelectSteering(int answer);


    const char *CurrentCarTypeSettingToString();
    const char *CurrentEngineSettingToString();
    const char *CurrentBrakeSettingToString();
    const char *CurrentSteeringSettingToString();

    int IsValidCheck();

    void PrintAssembledCarType();

    void PrintAssembledCarEngineType();

    void PrintAssembeldCarBrakeType();

    void PrintAssembledCarSteeringType();

    void RunProducedCar();

    void TestProducedCar();
};
