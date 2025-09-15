#include "PrintManager.h"

PrintManager &PrintManager::GetInstance() {
    static PrintManager print_manager;
    return print_manager;
}

void PrintManager::PrintPage(PageEnum page) const {
    printf(CLEAR_SCREEN);

    if(page == PageEnum::eCarTypePage) {
        PrintChoiceCarTypePage();
    }
    else if(page == PageEnum::eEnginePage) {
        PrintChoiceEngineTypePage();
    }
    else if(page == PageEnum::eBrakePage) {
        PrintChoiceBrakeTypePage();
    }
    else if(page == PageEnum::eSteeringPage) {
        PrintChoiceSteeringTypePage();
    }
    else if(page == PageEnum::eRunOrTestPage) {
        PrintChoiceRunAndTestPage();
    }

    printf("===============================\n");
}

void PrintManager::PrintChoiceCarTypePage() const {
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

void PrintManager::PrintChoiceEngineTypePage() const {
    printf("어떤 엔진을 탑재할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. 고장난 엔진\n");
}

void PrintManager::PrintChoiceBrakeTypePage() const {
    printf("어떤 제동장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
}

void PrintManager::PrintChoiceSteeringTypePage() const {
    printf("어떤 조향장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
}

void PrintManager::PrintChoiceRunAndTestPage() const {
    printf("멋진 차량이 완성되었습니다.\n");
    printf("어떤 동작을 할까요?\n");
    printf("0. 처음 화면으로 돌아가기\n");
    printf("1. RUN\n");
    printf("2. Test\n");
}
