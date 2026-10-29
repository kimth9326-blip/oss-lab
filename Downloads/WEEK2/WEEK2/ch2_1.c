/* [예제 2-1] 디렉터리 생성하기 — mkdir(2)
 *
 * 이 예제가 보여 주려는 것
 *   쉘에서 `mkdir han` 을 치는 일을 C 프로그램 안에서 mkdir() 함수로 한다.
 *   시스템 호출은 언제든 실패할 수 있으므로, 리턴값이 -1 이면 perror() 로
 *   실패 원인을 출력하고 끝내는 "기본 틀"을 익히는 것이 목적이다.
 *   이 틀(호출 → -1 검사 → perror → exit)은 이 장의 모든 예제에서 반복된다.
 *
 * 실행 결과: ./ch2_1.out  → han 디렉터리 생성 (화면에는 아무것도 안 나옴)
 *            다시 실행    → han: File exists  (이미 있으니 실패, 종료 코드 1) */
#include <sys/stat.h>   /* mkdir() 선언이 들어 있는 헤더 */
#include <stdlib.h>     /* exit() */
#include <stdio.h>      /* perror() */

int main() {
    /* mkdir(만들 디렉터리 이름, 권한)
     *   0755 = rwxr-xr-x : 소유자는 읽기·쓰기·실행, 나머지는 읽기·실행만.
     *   성공하면 0, 실패하면 -1 을 리턴하고 실패 원인은 errno 에 남긴다. */
    if (mkdir("han", 0711) == -1) {
        perror("han");   /* errno 를 읽어 "han: 원인" 형태로 출력 (예: han: File exists) */
        exit(1);         /* 실패했으니 0 이 아닌 값으로 종료. 쉘에서 $? 로 확인 가능 */
    }
}

