/* [예제 2-7] 디렉터리 이동하기 2 — open(2) + fchdir(2)
 *
 * 이 예제가 보여 주려는 것
 *   예제 2-6 과 결과는 같지만 방법이 다르다. chdir() 은 "이름"으로 이동하고,
 *   fchdir() 은 "파일 디스크립터"로 이동한다. 그래서 먼저 open() 으로 디렉터리를 열어
 *   번호(fd)를 받고, 그 번호를 fchdir() 에 넘긴다.
 *   디렉터리도 open() 으로 열 수 있다는 것, 그리고 fd 로도 이동이 된다는 것이 핵심이다.
 *   (실제로는 어떤 디렉터리로 갔다가 다시 돌아올 때, 원래 위치를 fd 로 잡아 두는 용도로 쓴다.)
 *
 * 실행 결과: 1.Current Directory: /home/jaeyeul/PKNU/WEEK2
 *            2.Current Directory: /home/jaeyeul/PKNU/WEEK2/bit
 *            bit 가 디렉터리가 아니라 일반 파일이면 → fchdir: Not a directory */
#include <fcntl.h>      /* open(), O_RDONLY */
#include <unistd.h>     /* fchdir(), getcwd(), close() */
#include <stdio.h>      /* printf(), perror(), BUFSIZ */
#include <stdlib.h>     /* free(), exit() */

int main() {
    char *cwd;
    int fd;             /* open() 이 돌려주는 파일 디스크립터(정수 번호) */

    /* 이동 전 위치 출력 */
    cwd = getcwd(NULL, BUFSIZ);
    printf("1.Current Directory: %s\n", cwd);
    free(cwd);

    /* 디렉터리 bit 를 읽기 전용으로 연다. 성공하면 0 이상의 번호, 실패하면 -1 */
    fd = open("bit", O_RDONLY);
    if (fd == -1) {
        perror("bit");          /* 예: bit: No such file or directory */
        exit(1);
    }
    /* 그 번호가 가리키는 디렉터리로 이동. bit 가 디렉터리가 아니면 -1 (ENOTDIR) */
    if (fchdir(fd) == -1) {
        perror("fchdir");       /* 예: fchdir: Not a directory */
        close(fd);
        exit(1);
    }

    /* 이동 후 위치 출력. 끝에 /bit 가 붙어 있으면 성공 */
    cwd = getcwd(NULL, BUFSIZ);
    printf("2.Current Directory: %s\n", cwd);

    close(fd);          /* 연 디스크립터 닫기 */
    free(cwd);
}
