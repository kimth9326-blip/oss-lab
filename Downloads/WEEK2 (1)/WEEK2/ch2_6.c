/* [예제 2-6] 디렉터리 이동하기 1 — chdir(2)
 *
 * 이 예제가 보여 주려는 것
 *   쉘의 `cd bit` 를 C 의 chdir() 로 한다. 이동 전과 후에 getcwd() 로 경로를 찍어
 *   실제로 옮겨 갔는지 눈으로 확인한다.
 *   중요한 포인트: 이동은 "이 프로그램(프로세스) 안에서만" 일어난다. 프로그램이 끝나고
 *   쉘에서 pwd 를 쳐 보면 쉘의 위치는 그대로다. 현재 디렉터리는 프로세스마다 따로 갖는
 *   정보이기 때문이다. (그래서 cd 는 외부 프로그램이 아니라 쉘 내장 명령이다.)
 *
 * 실행 결과: 1.Current Directory: /home/jaeyeul/PKNU/WEEK2
 *            2.Current Directory: /home/jaeyeul/PKNU/WEEK2/bit
 *            (끝난 뒤 쉘에서 pwd 를 쳐도 /home/jaeyeul/PKNU/WEEK2 그대로) */
#include <unistd.h>     /* chdir(), getcwd() */
#include <stdio.h>      /* printf(), BUFSIZ */
#include <stdlib.h>     /* free() */

int main() {
    char *cwd;

    /* 이동 전 위치 출력. getcwd(NULL, …) 은 예제 2-3 의 방식 2 (malloc 해서 돌려줌) */
    cwd = getcwd(NULL, BUFSIZ);
    printf("1.Current Directory: %s\n", cwd);
    free(cwd);          /* 아래에서 cwd 를 다시 받기 전에 먼저 반납 (안 하면 메모리 누수) */

    /* 현재 디렉터리를 bit 로 바꾼다. bit 가 없으면 -1 을 리턴하지만
     *   이 예제는 일부러 검사하지 않는다 (검사 넣기는 연습문제 9 번) */
    chdir("bit");

    /* 이동 후 위치 출력. 끝에 /bit 가 붙어 있으면 이동 성공 */
    cwd = getcwd(NULL, BUFSIZ);
    printf("2.Current Directory: %s\n", cwd);
    free(cwd);
}
