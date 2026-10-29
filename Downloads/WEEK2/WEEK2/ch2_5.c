/* [예제 2-5] 디렉터리명 변경하기 — rename(2)
 *
 * 이 예제가 보여 주려는 것
 *   쉘의 `mv han bit` 를 C 의 rename() 으로 한다. 파일이든 디렉터리든 같은 함수를 쓴다.
 *   틀은 예제 2-1 과 같다. 바꿀 대상(han)이 먼저 있어야 하므로 2-1 을 실행한 뒤에 돌린다.
 *
 * 실행 결과: han → bit 로 이름 변경 (화면에는 아무것도 안 나옴)
 *            han 이 없으면 → rename: No such file or directory  (종료 코드 1) */
#include <stdio.h>      /* rename(), perror() — rename 은 stdio.h 에 선언되어 있다 */
#include <stdlib.h>     /* exit() */

int main() {
    /* rename(현재 이름, 새 이름) : 성공 0, 실패 -1 */
    if (rename("han", "bit") == -1) {
        perror("rename");
        exit(1);
    }
}
