/* [예제 2-8] 디렉터리 내용 읽기 — opendir(3) / readdir(3) / closedir(3)
 *
 * 이 예제가 보여 주려는 것
 *   쉘의 `ls -i` 를 C 로 흉내 낸다. 디렉터리는 "이름과 inode 번호의 목록"이 들어 있는
 *   특수한 파일이고, 그 목록을 한 항목씩 꺼내 읽는 함수가 readdir() 이다.
 *   파일을 fopen → fgets 반복 → fclose 로 읽듯이, 디렉터리는
 *   opendir → readdir 반복 → closedir 로 읽는다. 이 세 함수 짝이 핵심이다.
 *
 * 실행 결과: Name : .        Inode : 8397070323793890647
 *            Name : ch2_1.c  Inode : 1619465790421035868
 *            ...  (현재 디렉터리의 모든 항목. . 과 .. 도 나오고, 순서는 정렬되어 있지 않다) */
#include <stdio.h>      /* printf(), perror() */
#include <stdlib.h>     /* exit() */
#include <sys/types.h>  /* ino_t 등 자료형 */
#include <dirent.h>     /* DIR, struct dirent, opendir(), readdir(), closedir() */

int main() {
    DIR *dp;                /* 열린 디렉터리를 가리키는 핸들. 파일의 FILE* 에 해당 */
    struct dirent *dent;    /* readdir 가 돌려주는 "항목 하나"의 정보 (이름, inode 번호 등) */

    /* 현재 디렉터리(".") 를 연다. 실패하면 NULL */
    dp = opendir(".");
    if (dp == NULL) {
        perror("opendir");
        exit(1);
    }

    /* readdir 는 부를 때마다 다음 항목을 하나씩 돌려주고, 더 없으면 NULL 을 돌려준다.
     *   그래서 NULL 이 나올 때까지 반복하면 모든 항목을 다 읽게 된다. */
    while ((dent = readdir(dp)) != NULL) {
        printf("Name : %s ", dent->d_name);                     /* 항목 이름 */
        printf("Inode : %lu\n", (unsigned long)dent->d_ino);    /* 그 항목의 inode 번호 */
    }

    closedir(dp);           /* 다 읽었으면 닫는다 */
}
