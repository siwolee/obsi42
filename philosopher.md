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

