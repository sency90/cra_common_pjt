# cra_common_pjt
CRA 공통과제

---
# Notice
printf()로 출력하는 한글이 깨져
아래와 같은 코드를 추가하였습니다.

```cpp
#pragma execution_character_set("utf-8")
#include <windows.h>
/* ... */

SetConsoleOutputCP(CP_UTF8);
SetConsoleCP(CP_UTF8);
```

# CheckList
D1 O
D2 O
D3 X
D4 O
D5 O

# Code Coverage
code_coverage.png 스크린샷 참고 부탁드립니다.
실제 coverage측정 결과는 coverage/index.html 에 있습니다.
