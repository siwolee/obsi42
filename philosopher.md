# 어떻게  작동하나요
- 아 일단 전역변수는 금지입니다
- 작동 원형은 아래와 같습니다 :
```sh
./pilo "number_of_philo" "time_to_die" "time_to_eat" "time_to_sleep" \
	[number_of_times_each_philosopher_must_eat(optional)]
```
	av[1] 철학자의 수
	av[2] 죽음에 이르기까지 걸리는 시간 (ms)
		식사 시간 사이 간격 혹은 시뮬레이션의 시작시간이 죽는 시간을 넘어가면, 죽음
	av[3] 식사에 걸리는 시간 (ms)
	av[4] 수면에 걸리는 시간 (ms)
	av[5] 각 철학자가 몇번 먹으면 끝나는지 (optional)
- 철학자의 번호는 1 ~ "number of philo" 입니다
- 철학자는 원형으로 앉아 있으며, 따라서 1번 철학자는 마지막 철학자 옆에 앉습니다. 
	모든 철학자는 순서대로 앉아 있습니다.
- 작동 시에는 모든 상태 변화가 아래와 같이 표시됩니다: 
	timestamp_in ms는 ms로 표시된 현재시간으로 ,
	X는 철학자의 번호로 대체됩니다.
``` sh
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```
- 모든 상태 변화는 다른 상태 변화 메시지와 섞여서 나타날 수 없습니다.
- 철학자의 죽음은 죽은 지 10ms 안에 표시되어야 합니다.
- 철학자를 죽이지 마세요!


# 개념공부
## Data Racing : 경쟁 상태
다른 곳에서 읽을 가능성이 있는 어떤 메모리 위치에 쓰기 작업을 하는 것..
프로그램이나 시스템등의 실행/출력 결과가 일정하지 않고, 입력의 타이밍, 실행되는 순서나 시간 등에 영향을 받게 되는 상황. 결과가 매번 달라진다.

### 레이스 컨디션
현재 작업이 제어할 수 없는 또다른 작업과의 진행 순서, 타이밍에 따라 결과가 달라질 수 있는 상황을 포괄적으로 일컬음. 데이터 레이스를 포함함

## Mutex :  상호 배제(mutual exclusion)
혹은 임계 구역, 영역(critical section)
서로 다른 프로세스/스레드의 처리 단위가 같이 접근해서는 안 되는 공유 영역
- 입장 구역(entry section) :  임계 구역을 시작하는 코드 부분
- 퇴장 구역(exit section) : 임계 영역을 종료하는 코드 부분
- 나머지 구역(remainder section)
  
## pthread : POSIX Thread의 약자
유닉스 계열 POSIX시스템에서 병렬 작동하는 소프트웨어를 작성하기 위하여 제공하는 API


# 함수공부
## 허용함수 (mende)
. memset, printf, malloc, free, write, usleep, 
gettimeofday, 
pthread_create, pthread_detach, pthread_join, 
pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

## 허용함수 (bonus)
memset, printf, malloc, free, write, fork, kill, exit, 
pthread_create, pthread_detach, pthread_join, 
usleep, gettimeofday, waitpid, 
sem_open, sem_close, sem_post, sem_wait, sem_unlink


## pthread_create

```c

int pthread_create(pthread_t*thread, // 스레드 식별 아이디 
	const pthread_attr_t*attr, // 스레드특성
	void*(*start_routine)(void *), //스레드가 실행했을 때 시작할 스레드 함수이름
	void *arg); //위 함수에 보낼 입력 파라미터
//리턴갑 스레드아이디
```
스레드를 생성하는 함수


## pthread_join

메인스레드에서 분기시킨 스레드가 종료하기를 기다리는 함수
(pthread_detach 함수를 통해 기다리지 않고 종료 가능)
```c
int pthread_join(pthread_t th, //스레드의 식별자
		     void **thread_return); //리턴값. status 

```
## sem_open
```c
sem_t * sem_open(  //세마포어 디스크립터
			const char * sem_name, //생성 또는 접근하고자 하는 세마포어의 이름
		     int oflags, //세마포어 생성 플래그 - O_CREAT / O_EXCL
		     ... ); //mode_t mode , unsigned int value
```
이름 있는 세마포어의 생성 및 접근
`sem_init()`으로 생성되는 무명 세마포어보다 느림
세마포어는 시스템이 살아있는 한 존재

반환한 세마포어는 `sem_wait()`  `sem_post()` 활용에 사용 가능
`sem_close()` 호출 전까지 사용가능
`sem_unlink()` 역시 가능하며, 모든 프로세스가 언링크하면 세마포어는 파괴됨

유명 세마포어는 `/dev/sem` 경로에 생성

## sem_close
```c
int sem_close(sem_t *sem);
```
returns 0; on error, -1 is returned


## sem_post
```c
sem_post(sem_t *sem);
```
세마포어 하나 증가(V 역할)

## sem_wait 
```c
sem_wait(sem_t *sem);
```
세마포어 하나 감소(P 역할)
뮤텍스를 사용하는 것과 같다.
세마포어를 하나 감소시키는 역할을 하고, 
세마포어가 0일 때는 1 이상이 될 때까지 스레드는 대기 상태
1 이상이 되면 대기상태에서 빠져나와 1 감소

**sem_init(sem_t *sem, int pshared, unsigned int value);**

첫번째 인자 :: 세마포어 객체를 초기화 할 세마포어를 받는다. (위의 sem_t semaphore가 여기 해당된다.)

두번째 인자 :: 여기에 0을 주지 않을경우 sem_init는 항상 ENOSYS 에러코드를 반환한다.(0을 쓰도록 한다.)

세번째 인자 :: 세마포어를 몇으로 초기화 할지 의미한다.(화장실 열쇠를 몇개로 시작할지 의미)
우리는 init을 쓸 수가 없다...


# 구조
## main  
변수확인  
pthread 선언  
뮤텍스 선언 * n (fork)Make  
뮤텍스 초기화 //정적 동적 초기화의 차이는?  
pthread create * n →&exec  
pthread join * n  
mutex destroy  

## 변수확인
if (ac not 4 or 5)  
exit  
while ac  
- if av 숫자 아니면  
- perror exi
## init philo struct  
struct env  
- int 철학자의수 av1  
- 죽는시간 av2  
- 먹는시간 av3  
- 자는시간 av4  
- 옵셔널: must eat av5  
- 포크 뮤텍스 n개 초기화struct philo[n]  
- pthread id →놔둠. 아직 할거없음..  
- 먹은 횟수 0  
- 구조체 timeval 마지막 식사 시작 시간 gettimeoftheday  
- 사용해야 하는 포크 n-1번(왼쪽)  
- 사용할 포크 n번(오른쪽)  
- Env
## EXEC 
> 메인 돌면서 실행시  pthread-create에서 사용할 함수  

exec( env)  
while (i < n)  
- eat(fork, tv)  


# Bonus
- 철학자= 자식프로세스
- 자식프로세스는  별도의 자원을 가지게 되므로, 공유하는  저장공간에 접근해서 모모니니터링링하하는  게 불가능 ->  각자의  프로세스에서 모니터링 필요.
- 이후 모니터링 프로세스에서는  프로세스 별로  스레드  분기해서 확인해줌
- 스레드에서는 프로세스를  waitpid로 기다리다가, waitpid될 경우 나머지를 kill
- 