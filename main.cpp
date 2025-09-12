// main.cpp
#ifdef _DEBUG

#include "gmock/gmock.h"

int main() {
  testing::InitGoogleMock();
  return RUN_ALL_TESTS();
}

#else

#include <stdio.h>

#include "cal.cpp"
int main() {
  Cal cal;
  int a = 1, b = 2;
  char input;

  // 사용자에게 분기 선택 메시지 출력
  printf(
      "에러 경로를 실행하려면 'e'를 입력하세요. 그 외의 입력은 정상 경로를 "
      "실행합니다: ");
  input = getchar();

  // 사용자 입력에 따른 분기 처리
  if (input == 'e') {
    // 음수 결과를 유도하여 에러 분기로 들어감
    a = -3;
    b = 1;
  }

  int ret = cal.getSum(a, b);

  if (ret < 0) {
    printf("Error: Negative sum encountered.\n");
  } else {
    printf("Result: %d\n", ret);
  }
  return 0;
}

#endif