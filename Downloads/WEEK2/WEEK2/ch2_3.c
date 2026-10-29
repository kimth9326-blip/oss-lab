/* [예제 2-3] 현재 디렉터리의 위치 검색하기 1 — getcwd(3)
 *
 * 이 예제가 보여 주려는 것
 *   getcwd() 는 "지금 이 프로그램이 서 있는 디렉터리의 경로"를 문자열로 알려 준다.
 *   쉘의 pwd 와 같은 일이다. 이 함수는 경로를 담을 공간(버퍼)을 어떻게 주느냐에 따라
 *   세 가지 방식으로 쓸 수 있고, 이 예제는 그 세 가지를 차례로 해 본다.
 *
 *     방식 1  내가 배열을 만들어 넘긴다            → wd1
 *     방식 2  NULL 을 넘겨 getcwd 가 malloc 하게 한다 → cwd1  (크기는 내가 지정)
 *     방식 3  NULL 과 0 을 넘긴다                  → cwd2  (크기도 getcwd 가 경로에 맞게 정함)
 *
 *   세 방식 모두 결과는 같은 경로다. 마지막에 방식 1 을 한 번 더 하되 배열을 10바이트로
 *   아주 작게 잡아서, "버퍼가 경로보다 짧으면 getcwd 는 실패한다"는 것을 직접 보여 준다.
 *   즉 마지막 오류 메시지는 코드가 잘못된 것이 아니라 일부러 만든 장면이다.
 *
 * 실행 결과: wd1 = /home/jaeyeul/PKNU/WEEK2
 *            cwd1 = /home/jaeyeul/PKNU/WEEK2
 *            cwd2 = /home/jaeyeul/PKNU/WEEK2
 *            getcwd: Numerical result out of range
 *              → 경로가 25글자라 10바이트 배열에 안 들어감. errno 가 ERANGE 라서 이 문장이 나온다. */
#include <unistd.h>     /* getcwd() 선언 */
#include <stdlib.h>     /* free(), exit() */
#include <stdio.h>      /* printf(), perror(), BUFSIZ */

int main() {
    char *cwd;          /* 방식 2, 3 에서 getcwd 가 malloc 해 준 주소를 받을 포인터 */
    char wd1[BUFSIZ];   /* 방식 1 용 배열. BUFSIZ 는 stdio.h 에 8192 로 정의된 상수 */
    char wd2[10];       /* 방식 1 을 다시 하되 일부러 작게 잡은 배열 (실패 장면용) */

    /* 방식 1: 내가 만든 배열 wd1 에 경로를 써 달라고 한다. 두 번째 인자는 그 배열의 크기.
     *   성공하면 wd1 의 주소, 실패하면 NULL 을 리턴한다. */
    getcwd(wd1, BUFSIZ);
    printf("wd1 = %s\n", wd1);

    /* 방식 2: 버퍼 자리에 NULL 을 주면 getcwd 가 BUFSIZ 바이트를 malloc 해서 경로를 넣고
     *   그 주소를 리턴한다. 내가 만든 메모리가 아니므로 다 쓰면 free 해야 한다. */
    cwd = getcwd(NULL, BUFSIZ);
    printf("cwd1 = %s\n", cwd);
    free(cwd);          /* getcwd 가 malloc 한 8192 바이트 반납 */

    /* 방식 3: 크기까지 0 으로 주면 getcwd 가 경로 길이에 딱 맞는 크기만 malloc 한다.
     *   가장 편한 방식. 역시 free 필요. (방식 2, 3 은 리눅스 glibc 의 확장 기능) */
    cwd = getcwd(NULL, 0);
    printf("cwd2 = %s\n", cwd);
    free(cwd);

    /* 실패 장면: 10바이트 배열에 경로를 담으라고 한다.
     *   현재 경로 "/home/jaeyeul/PKNU/WEEK2" 는 25글자 + 끝 표시(NUL) = 26바이트가 필요하므로
     *   getcwd 는 NULL 을 리턴하고 errno 에 ERANGE 를 남긴다.
     *   → 버퍼를 직접 넘기는 방식은 크기를 잘못 잡으면 실패하니 리턴값을 꼭 검사해야 한다. */
    if (getcwd(wd2, 10) == NULL) {
        perror("getcwd");   /* ERANGE 의 기본 문구가 "Numerical result out of range" */
        exit(1);
    }
}
