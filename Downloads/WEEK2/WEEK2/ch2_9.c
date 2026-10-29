/* [예제 2-9] 디렉터리의 내용을 읽는 위치 파악하기 — telldir / seekdir / rewinddir(3)
 *
 * 이 예제가 보여 주려는 것
 *   readdir() 는 "지금 어디까지 읽었는지" 위치를 기억하면서 한 항목씩 넘겨준다.
 *   이 위치를 다루는 함수 세 개를 익힌다.
 *     telldir(dp)        지금 읽기 위치를 숫자로 알려 준다
 *     rewinddir(dp)      읽기 위치를 맨 처음으로 되돌린다  (다시 처음부터 읽고 싶을 때)
 *     seekdir(dp, loc)   telldir 로 받아 둔 위치 loc 로 되돌아간다
 *   파일에서 ftell / rewind / fseek 를 쓰는 것과 같은 개념이다.
 *
 *   주의: telldir 의 숫자는 "몇 번째 항목"이 아니라 파일 시스템 내부의 위치 값이라
 *   크기가 제멋대로처럼 보인다. 값 자체를 해석하지 말고 seekdir 에 다시 넘기는 용도로만 쓴다.
 *
 * 실행 결과: Start Position : 0
 *            Read : ch2_1.c -> Cur Position : 1619465790421035868
 *            ...  (항목마다 한 줄)
 *            ** Directory Position Rewind **
 *            Cur Position : 0
 *            ** Move Directory Pointer **
 *            Cur Position : 333999389100956450
 *            Read : textbook_original     (위치 값과 항목 이름은 환경마다 다르다) */
#include <stdio.h>      /* printf(), fprintf(), perror() */
#include <stdlib.h>     /* exit() */
#include <sys/types.h>  /* 자료형 */
#include <dirent.h>     /* DIR, struct dirent, opendir/readdir/closedir, telldir/seekdir/rewinddir */

int main() {
    DIR *dp;
    struct dirent *dent;
    long loc;               /* telldir 가 돌려주는 위치 값을 저장할 변수 */

    dp = opendir(".");
    if (dp == NULL) {
        perror("opendir");
        exit(1);
    }

    /* 1) 처음 위치. 아직 아무것도 안 읽었으니 0 */
    printf("Start Position : %ld\n", telldir(dp));

    /* 2) 끝까지 읽으면서 한 항목 읽을 때마다 위치가 어떻게 바뀌는지 찍어 본다 */
    while ((dent = readdir(dp)) != NULL) {
        printf("Read : %s -> ", dent->d_name);
        printf("Cur Position : %ld\n", telldir(dp));
    }

    /* 3) 위치를 맨 처음으로 되돌린다. 다시 0 이 찍힌다 */
    printf("** Directory Position Rewind **\n");
    rewinddir(dp);
    printf("Cur Position : %ld\n", telldir(dp));

    /* 4) 항목 하나를 읽어 위치를 한 칸 옮긴 뒤, 그 위치를 telldir 로 저장했다가
     *    seekdir 로 같은 위치로 되돌아간다. 위치가 같으니 다음 readdir 는 두 번째 항목을 준다. */
    printf("** Move Directory Pointer **\n");
    readdir(dp);                /* 첫 항목을 읽어서 넘긴다 (내용은 안 씀) */
    loc = telldir(dp);          /* 지금 위치 저장 */
    seekdir(dp, loc);           /* 저장한 위치로 이동 (같은 자리) */
    printf("Cur Position : %ld\n", telldir(dp));
    if ((dent = readdir(dp)) == NULL) {     /* 두 번째 항목 읽기. 없으면 종료 */
        fprintf(stderr, "No more entry\n");
        closedir(dp);
        exit(1);
    }
    printf("Read : %s \n", dent->d_name);
    closedir(dp);
}
