/* [예제 2-2] 디렉터리 삭제하기 — rmdir(2)
 *
 * 이 예제가 보여 주려는 것
 *   쉘의 `rmdir han` 을 C 의 rmdir() 로 한다. 예제 2-1 과 완전히 같은 틀이다.
 *   rmdir() 는 "비어 있는" 디렉터리만 지운다. 안에 파일이 있으면
 *   "Directory not empty" 로 실패한다는 점만 다르다.
 *
 * 실행 결과: ./ch2_2.out  → han 디렉터리 삭제 (화면에는 아무것도 안 나옴)
 *            han 이 없으면 → han: No such file or directory  (종료 코드 1) */
#include <unistd.h>     /* rmdir() 선언 */
#include <stdlib.h>     /* exit() */
#include <stdio.h>      /* perror() */

int main() {
    /* rmdir(지울 디렉터리 이름) : 성공 0, 실패 -1 */
    if (rmdir("han") == -1) {
        perror("han");   /* 예: han: No such file or directory */
        exit(1);
    }
}
