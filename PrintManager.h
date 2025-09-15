#pragma once
#include <cstdio>
#include "IParts.h"
#include "CommonFunction.h"
#include "PageEnum.h"

#ifdef _WIN32
#pragma execution_character_set("utf-8")
#include <windows.h>
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif

#define CLEAR_SCREEN "\033[H\033[2J"

class PrintManager {
private:
    PrintManager() {
        CommonFunction::GetInstance().PrintSettingForKorean();
    }

public:
    static PrintManager &GetInstance();

public:
    void PrintPage(PageEnum page) const;

private:
    void PrintChoiceCarTypePage() const;
    void PrintChoiceEngineTypePage() const;
    void PrintChoiceBrakeTypePage() const;
    void PrintChoiceSteeringTypePage() const;
    void PrintChoiceRunAndTestPage() const;
};

