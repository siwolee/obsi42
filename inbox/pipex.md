> pipex 스터디 노션 링크

관련 함수 설명
https://bigpel66.oopy.io/library/42/inner-circle/8


## Mendetory
`./pipex infile "ls -l" "wc -l" outfile`
./programname filename1 "cmd1" "cmd2" filename2
`< file1 cmd1 | cmd2 > file2`
위와 같이 작동

## Bonus
- cmd 여러 개일 때
- << , >> 지원
- 첫 매개변수가 here_doc일 때 확인

# 🌈 허용 함수
- open, close, read, write, malloc, free, 
- perror, strerror, 
- access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid 
- ft_printf and any equivalent YOU coded

# 🌈 구현해야해용
- [ ] 들어온 매개변수 갯수 검사 
	- [x] 멘데 : 4개 아니면 fail
	- [x] 보너스 : 4개 이상으로
	- [ ] 히어독 : ?
- [ ] 유효성 검사
	- [ ] 인파일
	- [ ] 명령어
	- [ ] 아웃파일 _ o_creat
- [x] pipe 2개
	- [ ] 에러처리 필요
- [ ] infile > pipe0으로 보내기
- [ ] fork 명령어 갯수 + 1
	- [ ] 명령어번호 따라서 = 0번읽기 / 1번쓰기 , 홀수는 1번읽기/0번쓰기
	- [ ] 마지막 자식 명령어는 읽고 나서 아웃파일 fd에 쓰기
 - [ ] waitpid : 마지막 child
 - [ ] 히어독 어캄 << >>?
 - [ ] 파이프라인 병렬 처리

# 🌈 오류를 처리합니다
- [ ] infile이 없을 경우
- [ ] infile 권한이 없을 경우
- [ ] outfile 권한이 없을 경우
- [ ] 명령어 또는 

https://devraphy.tistory.com/339
파이프라인 병렬 처리



### unistd.h (fcntl.h)
open / close / read/ write 
fd 기준 읽기 / 쓰기 함수

### stdlib.h
- malloc
- free
heap 메모리 할당/ 해제 함수

## Access
- unistd.h
path에 해당하는 파일 유무 확인 / 권한 확인
불가시 -1 반환. mode 여러개를 평가하는 건 가능하지만 그때 분리해서 확인은 어려움
```c
#define F_OK 0
#define X_OK (1<<0) //executeable
#define W_OK (1<<1) //writeable
#define R_OK (1<<2) //readable

int mode;
access("path/path.ex", mode);
```

## Unlink
- unistd.h
하드 링크를 끊는 함수.
하드 링크가 전부 끊어진 파일은 삭제됨.
하드링크의 예시 : . ..
```c
int unlink(const char *path);
```
반환값은 실패시 -1

## fork
- unistd.h
```c
pid_t fork(void);
```
실행시 실행 함수는 부모 프로세스로, 자식 프로세스가 생기게 된다. 
메모리의 상태를 복사한다(같은 곳을 가리키는 게 아니다)
PC(program counter)를 복사하기 때문에, 함수 호출 이후에 context(process 상태)를 갖게 된다,. 
### context switching : CPU가 실행하는 process를 바꾸는 과정
https://up-to-date-items.tistory.com/79


### 반환값
부모 프로세스 : 자식 프로세스의 pid
자식 프로세스 : 0
오류 : 부모 프로세스에 -1 반환

### fork 후 malloc 된 메모리 찾기 > 해제됨
(https://stackoverflow.com/posts/5429592/timeline)

When you call `fork()`, a copy of the calling process is created. This child process is (almost) exactly the same as the parent, i.e. memory allocated by `malloc()` is preserved and you're free to read or modify it. The modifications will not be visible to the parent process, though, as the parent and child processes are completely separate.

When you call `exec()` in the child, the child process is replaced by a new process. From execve(2):

```kotlin
execve() does not return on success, and the text, data, bss, and stack
of the calling process are overwritten by that of the program loaded.
```

By overwriting the `data` segment, the `exec()` call effectively reclaims the memory that was allocated before by `malloc()`.


## wait
- sys/wait.h
```c
pid_t    wait(int *status);
```
부모 프로세스가 자식 프로세스가 끝날 때까지 기다리면서 고아 프로세스 방지

### 프로세스의 상태
- 고아 프로세스
	부모 프로세스 먼저 종료시
	자식 프로세스 ppid 1 (parent pid)

### 리턴값
자식 프로세스의 pid : 자식 프로세스가 return 혹은 exit에 의해 실행종료시
\-1 : 시그널에 의한 종료시 (errno : EINTR)

### 매개변수 status 
자식 프로세스가 종료되는 시점에 기록된 정보 기록
- 종료 코드
- 시그널
4바이트 int의 인덱스 0, 1, 2, 3중 실사용 공간은 2(종료코드) 3(시그널) // 이거 뭔지 모르겠다 ㅎㅎㅎ

```c
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	int man;
	man  = 0;
	int *status;
	if (access("bcd" , F_OK | X_OK) < 0) // 파일 존재 및 실행 가능 확인
	{
		printf("no file exist\n");
		return (0);
	}
	printf("file exist\n");
	if (!fork())
	{
		printf("자식 프로세스입니다\n");
		man ++; //이후 자식 프로세스에서만 올라가는 카운트
	}
	else
	{
		printf("부모 프로세스입니다\n");
		if (wait(status) > 0)
			printf("자식 프로세스가 정상 종료되었습니다\n");
		printf("%d\n", *status);
	}
	printf("최종 값은? %d\n", man); // 부모 프로세스 끝난 후 자식 프로세스 실행
}

file exist
부모 프로세스입니다
자식 프로세스입니다
최종 값은? 1
자식 프로세스가 정상 종료되었습니다 >> 기다린 후에 
0
최종 값은? 0 >> 부모 프로세스가 끝나는 걸 알 수 있음
```


## waitpid
- sys/wait.h
```c
pid_t waitpid(pid_t pid, int *status, int options);
```
pid 정보를 넘겨서 특정 pid 종료를 기다릴 수가 있어용
만약 pid 에 -1 주면 wait과 동일하게 동작해용
![[Pasted image 20230123174143.png]]
*갓명헌 따라하가*

### option
WUNTRACED → STOP 시그널을 통해 실행을 멈춘 자식 프로세스의 status에 대해서 반환
WCONTINUED → CONT 시그널을 통해 실행을 재개한 자식 프로세스의 status에 대해서 반환
WNOHANG → 자식 프로세스의 종료를 기다리지 않고 즉시 자식 프로세스의 status에 대해서 반환
WNOHANG을 사용하면 자식 프로세스의 종료를 기다리지 않기 때문에 WNOHANG을 사용한 waitpid 함수의 호출 시점에 자식 프로세스가 종료되었을 수도 있고 그렇지 않을 수도 있다. 두 경우에는 waitpid의 반환 값이 서로 다르다. WNOHANG을 사용하기 이전에 자식 프로세스가 종료된 경우에는 status가 올바른 값이므로, waitpid의 반환 값은 자식 프로세스의 pid가 된다. 반대로 옵션이 사용되었을 때 자식 프로세스가 종료되지 않은 상태라면 status가 올바르지 않은 값이 되므로, waitpid의 반환 값은 0이 된다.
출처 : https://bigpel66.oopy.io/library/42/inner-circle/8

wait은 stop, cont 시그널을 받은 자식 프로세스에 대해서 -1을 리턴한다. 따라서 이런 경우에 유용하게 이용 가능.

보통의 경우에는 부모 프로세스가 정지(block한 상태에서 흐름대로 동작한다. wait과 비슷하게 동작하는 것이다. 대신에 멀티프로세싱을 하고 싶을 경우에는 `WHOHANG`을 사용하게 된다. 옵션 사용시 자식 프로세스의 종료를 기다리지 않고도 자식 프로세스의 상태 변화에 대해서 stasus를 즉시 얻음으로서, Non-block 상태로 이어갈 수 있다.


일단 시도해본다.
```c
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int ac, char **av)
{
	int i;
	int e;
	int status;
	pid_t pid[3];
	int fd;

	i = 0;
	while (++i < ac)
	{
		if (access(av[i] , F_OK | W_OK) < 0)
		{
			printf("cannot access file\n");
			return (0);
		}
		printf("%s file check : OK \n", av[i]);
		i++;
	}
	i = 0;
	while (i < ac -1)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			printf("fork %d canceled : return\n", i);
			e = 0;
			while (e < i)
				waitpid(pid[e], &status, 0);
		}
		else if (pid[i] == 0)
		{
			fd = open(av[i + 1], O_RDWR);
			write(fd, "write fine", 10);
			close(fd);
			printf("자식 프로세스가 완료되었습니다.\n");
			return (i);
		}
		i++;
	}
	printf("부모 프로세스입니다\n");
	e = 0;
	while (e < i)
	{
		fd = waitpid(pid[e],&status, 0);
		printf("기다렸습니다 : 자식 pid %d, %d번째\n", fd, e);
		printf("Exit code : %d, signal : %d \n", WEXITSTATUS(status), WTERMSIG(status));
		e++;
	}
	printf("정상 종료되었습니다.\n");
}

```

```c
➜  pipex git:(main) ./a.out a b c //wait
a file check : OK 
c file check : OK 
부모 프로세스입니다
자식 프로세스가 완료되었습니다.
자식 프로세스가 완료되었습니다.
기다렸습니다 : 자식 pid 72979, 0번째 // 순서에 따라 종료되는 게 아닌, 종료되는 대로 결과를 받는다는 걸 알수있음
Exit code : 1, signal : 0 
기다렸습니다 : 자식 pid 72978, 1번째
Exit code : 0, signal : 0 
자식 프로세스가 완료되었습니다.
기다렸습니다 : 자식 pid 72980, 2번째
Exit code : 2, signal : 0 
정상 종료되었습니다.
➜  pipex git:(main) gcc test.c -g
➜  pipex git:(main) ./a.out a b c // waitpid를 통한 pid 지정
a file check : OK 
c file check : OK 
부모 프로세스입니다
자식 프로세스가 완료되었습니다.
자식 프로세스가 완료되었습니다.
자식 프로세스가 완료되었습니다.
기다렸습니다 : 자식 pid 73387, 0번째
Exit code : 0, signal : 0 
기다렸습니다 : 자식 pid 73388, 1번째
Exit code : 1, signal : 0 
기다렸습니다 : 자식 pid 73389, 2번째
Exit code : 2, signal : 0 
정상 종료되었습니다.
```


이후 `WNOHANG`을 이용하는 부분은 좀 어렵다...........
이건 차차 알아보도록 하자

## dup
- unistd.h
파일 디스크립터를 복제하는 함수 - 다른 fd지만 같은 파일을 가리키는, 현재까지 사용되지 않았던, 사용된 다음 fd 를 반환한다.
```c
int dup(int fd);
```
파일 디스크립터를 여러 개 열 경우 별도의 File table 내 entry
dup()의 경우에는 같은 entry를 참조하며, f_count값만 올라감.

문제시 return -1

## dup2
- unistd.h
파일 디스크립터를 재할당하는 함수. 
지정한 fd가 사용 중이라면, 사전에 열려 있던 파일을 닫아서 해제한 후에 해당 번호를 할당하게 된다.
```c
int dup2(int fd1, int fd2);
```

문제시 return -1
fd1의 파일 디스크립터가 fd2의 파일 디스크립터로 복제됨
fd2의 파일 디스크립터가 fd1과 같은 파일을 가리키게 됨

### 존재이유
pipe 함수와 같이 사용시,
프로세스 간에 0 1 인덱스를 fd로 사용시
dup2(pidp_fd, 0);
파일 디스크립터 0이 pipe_fd를 가리키게 됨


## pipe
- unistd.h
```c
int pipe(int fd[2]); //fd[0] = IN fd[1] = OUT
```

### IPC (Inter Process Communication)
프로세스 간의 통신
- 파일
- 메세지 큐
- 공유 메모리 소켓 등

fork 된 프로세스 사이에서는 시그널 / status를 주고 받을 수 있지만, 상태 공유, 수행 동작 정의 등에만 유효하고 실제 데이터를 통신시키기 위해서는 pipe가 필요함.
pipe로 fd를 열게 됨 -> 이는 파일에 대한 게 아닌 운영체제로부터 할당 받은 특정 버퍼를 가리킴. 
(그 버퍼 크기만큼만 가능)
단방향 통신으로 한쪽에서는 read / 반대쪽 write.
(각 프로세스가 read write 를 위한 2개의 파이프가 필요함)

fd를 사용하면, 여러 개의 프로세스에서 동일한 파일에 접근하여 통신이 가능.
복제된 프로세스 사이에서는 메모리를 복제하기 때문에, 
복제 이전에 pipe를 통해서 파일 디스크립터를 읽기/쓰기 용도로 연결한다면 그 파이프를 계속 쓸 수 있게 됨



## execve
- unistd.h
```c
int execve(const char *file, char * const *argv, char * const *envp);
```
매개변수로 실행할 파일 경로, 매개변수,  환경변수(사용시, 미사용시 NULL)을 넘기게 된다.
실행시 0 또는 -1(오류) 반환.

```c
int main(int ac, char **av)
{
	av++;
	if (access("bunny.c", F_OK | X_OK) == -1)
		return (1);
	if (execve("/usr/bin/gcc", av, NULL) == -1)
		{
			printf("gcc failed\n");
			return (1);
		}
	// if (execve("./bum", av + 2, NULL) == -1)
	// {
	// 	printf("exec failed\n");
	// 	return (1);
	// }
	printf("sucess\n");
	return (0);
}
➜  pipex git:(main) ./test gcc bunny.c -o bum
➜  pipex git:(main) gcc exec.c -o test       
➜  pipex git:(main) rm bum
➜  pipex git:(main) gcc exec.c -o test
➜  pipex git:(main) ./test gcc bunny.c -o bum
➜  pipex git:(main) ./bum                    
NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
NNNNNNNNNNNNXK0KXNNNNNNNNNNNNNNNNNNNNNNN
NNNNNNNNNNKkl,'':ox0XXNNNNNNNNNNNNNNNNNN
NNNNNNNNXOc.      .dKXNNNNNNNNNNNNNNNNNN
NNNNNNNXx,.     .:xKXNNNNNNNNNNNNNNNNNNN
NNNKOdc;.     .;kXNNNNNNNNNNNNNNNNNNNNNN
X0d;.       .,dKNNNNNNNNNNXXKKKKOdodOXNN
d,.         .'coodxxxxxdoc:,''''.   .dXN
o.               .......            .dXN
0c....                             'dXNN
NX0OOx,                            .lOXN
NNNNN0:.                           .:OXN
NNX0x;.            ...........     .;OXN
0o;..       .,clodxxkkOOO00Okdc..   .'lO
k'   ..',;:okKNNNNNNNNNNNNNNNNXOdc'....o
XOdlox0KKXXNNNNNNNNNNNNNNNNNNNNNNX0kxxOK
NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
```
처음에 안됐던 이유 : gcc 경로 앞에 \\ 를 안붙임 ㅎㅎ
그리고 만들어진 파일을 바로 실행시켜볼려고 했는데 안됐다
그리고 왜 gcc 실행하는데 gcc를 다시 실행인자로 넣어줘야 하는지...? 모르겠네용

https://www.it-note.kr/157
> execve(2)만 system call 함수이며, 나머지 execl(3), execlp(3), execle(3), execv(3), execvp(3), execvpe(3)는 wrapping 함수...

뭔소리지?
# System call 함수와 Libraray 함수의 특징
1. 리턴 타입과 값의 차이
	system call 함수는 대부분 int 반환으로, 오류는 -1 이고 정상이면 0 또는 1의 값을 리턴
	오류 값 리턴시, errno라는 전역변수에 오류 코드 저장
	상세 오류 내용에 대해서는 errno라는 전역변수에 오류 코드가 저장된다. 오류 내용을 문자열로 표시하기 위해서는 strerror(errno)를 통해서 확인할 수 있다 
	*무슨 소린지 모르겠음*
2. 





# ERROR
## pipe를  두개만 쓸 때, 파이프 재사용 시 stdin이 제대로 먹지 않음
해결 : 파이프를 닫고 다시 열어준다.
첫번째 / 두번째 / 마지막 커맨드에서는 필요가 없다. 
중간 커맨드에서 포크뜨기 전에 이번에 out으로 재사용할 파이프를 닫고 다시 열어준다.

## 중간 커맨드에서 stdin을 계속 받고 있음
해당 파이프의 아웃이 닫혀있어야 stdin을 받지 않는다.....

## 이미 존재하는 파일을 열 시, errno 13 (EACCES) 발생
## 혹은 O_CREAT로 생성 시 권한이 제대로 설정되지 않음.
https://wariua.github.io/man-pages-ko/open%282%29/
`EACCES`
파일에 요청한 접근 방식이 허용되지 않거나, `pathname` 경로 선두부의 한 디렉터리에 대해 탐색 권한이 거부되었거나, 파일이 아직 존재하지 않고 부모 디렉터리에 대한 쓰기 접근이 허용되지 않는다. ([path_resolution(7)](https://wariua.github.io/man-pages-ko/path_resolution(7)/)도 참고.)

`EACCES`
`O_CREAT`을 지정했는데, sysctl 항목 `protected_fifos`나 `protected_regular`가 켜져 있고, 파일이 이미 존재하며 FIFO 또는 정규 파일이고, 파일 소유자가 현재 사용자도 아니고 그 파일을 담은 디렉터리의 소유자도 아니며, 담은 디렉터리가 기타 또는 그룹이 쓰기 가능이면서 스티키이다. 자세한 내용은 [proc(5)](https://wariua.github.io/man-pages-ko/proc(5)/)의 `/proc/sys/fs/protected_fifos`와 `/proc/sys/fs/protected_regular` 설명을 보라.

O_CREAT로 없던 파일을 제작 시, 뒤에 설정해준 모드를 통해서 권한이 설정된다. (모드가 없을 경우 O_CREAT 옵션은 무용지물하다. https://linux.die.net/man/2/open)
그러나 666으로 모드를 넣어줬음에도 파일을 다시 열었을 때 권한 없음이 뜨고, 실제로도 파일 권한 설정이 411로 되어 있다..

```c
/tt infile "cat -e" "grep cs" "cat -e" outfile
ac : 6
errno : 13

-r----x--x  1 siwolee  2022_seoul      64 Feb 10 00:47 outfile
```

일단 존재하는 파일을 chmod를 이용해서 666으로 권한을 설정해준 후 실행시키면 잘 열린다.
그렇다면 O_CREAT의 문제라는 것인데...

무슨 변수가 있을까?
일단 실행권한을 줄 필요 없이 666으로만 진행하고, 몇 가지 다른 방식을 써 보기로 했다. 
```c
fd[0]= open("000", O_RDWR|O_TRUNC|O_CREAT, 666);
fd[1]= open("001", O_RDWR|O_TRUNC|O_CREAT, 666);
fd[2]= open("002", O_RDWR|O_TRUNC|O_CREAT, 666);
fd[3]= open("003", O_RDWR|O_TRUNC|O_CREAT, 666);
fd[4]= open("004", O_RDWR|O_TRUNC|O_CREAT, 666);
fd[5]= open("005", O_RDWR|O_TRUNC|O_CREAT, 666);

//result
--w---x---  1 siwolee  2022_seoul      0 Feb 10 10:22 000
--w---x---  1 siwolee  2022_seoul      0 Feb 10 10:22 001
--w---x---  1 siwolee  2022_seoul      0 Feb 10 10:22 002
--w---x---  1 siwolee  2022_seoul      0 Feb 10 10:22 003
--w---x---  1 siwolee  2022_seoul      0 Feb 10 10:22 004
--w---x---  1 siwolee  2022_seoul      0 Feb 10 10:22 005
```
엉뚱한 권한 - 210?
여튼 여러개가 똑같이 들어가고 있으니 오류는 아니고 규칙이 있는 듯

```c
fd[0]= open("000", O_RDWR|O_TRUNC|O_CREAT, 666);
fd[1]= open("001", O_RDWR|O_TRUNC|O_CREAT, 0666);
fd[2]= open("002", O_RDWR|O_TRUNC|O_CREAT, 00666);

--w---x---  1 siwolee  2022_seoul      0 Feb 10 10:26 000
-rw-r--r--  1 siwolee  2022_seoul      0 Feb 10 10:26 001
-rw-r--r--  1 siwolee  2022_seoul      0 Feb 10 10:26 002
```
앞에 0을 붙이니까 그나마 비슷하게 나왔다.

```c
fd[0]= open("000", O_RDWR|O_TRUNC|O_CREAT, 666);
fd[1]= open("001", O_WRONLY|O_TRUNC|O_CREAT, 666);
fd[2]= open("002", O_RDWR|O_TRUNC|O_CREAT, 0666);
fd[3]= open("003", O_WRONLY|O_TRUNC|O_CREAT, 0666);
fd[4]= open("004", O_RDWR|O_TRUNC|O_CREAT, 00666);
fd[5]= open("005", O_WRONLY|O_TRUNC|O_CREAT, 00666);

--w---x---  1 siwolee  2022_seoul      0 Feb 10 10:34 000
--w---x---  1 siwolee  2022_seoul      0 Feb 10 10:34 001
-rw-r--r--  1 siwolee  2022_seoul      0 Feb 10 10:34 002
-rw-r--r--  1 siwolee  2022_seoul      0 Feb 10 10:34 003
-rw-r--r--  1 siwolee  2022_seoul      0 Feb 10 10:34 004
-rw-r--r--  1 siwolee  2022_seoul      0 Feb 10 10:34 005
```

일단 0666, 0644, 0664 다 시도해 봤을 때 클러스터 맥에서는 0644만 나온다.
하지만 이 상태로도 실행은 문제 없이 되더라. 앞에 0을 빼먹지 마세요.
아무래도 셀프 권한이 없는 건가? 싶어서 집 가서 시도해볼 예정.

