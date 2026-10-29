/* [예제 2-4] 현재 디렉터리의 위치 검색하기 2 — get_current_dir_name(3)
 *
 * 이 예제가 보여 주려는 것
 *   예제 2-3 의 getcwd() 와 같은 일을 하는, 더 간단한 함수가 하나 더 있다.
 *   get_current_dir_name() 은 인자 없이 부르면 경로 길이에 맞게 malloc 한 문자열을 돌려준다.
 *   단, 이 함수는 표준이 아니라 리눅스(GNU) 전용이라서 코드 맨 위에 #define _GNU_SOURCE 를
 *   써 줘야만 헤더에서 선언이 보인다. 이 줄이 이 예제의 핵심이다.
 *
 * 실행 결과: cwd = /home/jaeyeul/PKNU/WEEK2 */
#define _GNU_SOURCE     /* "GNU 확장 함수도 쓰겠다"는 선언. 반드시 모든 #include 보다 앞에.
                         *  이 줄을 빼면 컴파일은 되지만(경고만 남) 실행하면 Segmentation fault */
#include <unistd.h>     /* get_current_dir_name() 선언 (_GNU_SOURCE 가 있어야 보인다) */
#include <stdlib.h>     /* free(), exit() */
#include <stdio.h>      /* printf(), perror() */

int main() {
    char *cwd;          /* 함수가 malloc 해 준 문자열의 주소를 받을 포인터 */

    /* 인자 없음. 현재 경로를 malloc 한 문자열로 리턴. 실패하면 NULL */
    cwd = get_current_dir_name();
    if (cwd == NULL) {
        perror("get_current_dir_name");
        exit(1);
    }
    printf("cwd = %s\n", cwd);
    free(cwd);          /* 함수가 malloc 한 메모리 반납 */
}
