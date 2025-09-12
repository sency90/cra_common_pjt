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
