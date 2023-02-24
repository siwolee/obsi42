[[gcc compiler]]




https://jaeseokim.dev/C/C-vscode-debugger-사용하기/
여기서  나온  makefile을 공부하고, 가지고 있는 makefile의 개념을 정립하고자 한다.
https://www.tuwlab.com/ece/27193 참고


## makefile = 빌드 툴

![[Pasted image 20230102175151.png]]
세 개의 소스파일을 각각 컴파일하여 \*.o file을 생성하고,
이들을 한데 묶는 링크 과정을 통해서 실행파일 \*.out을 생성.
타 파일에 작성된 함수를 메인에서 호출하는 의존성이 존재

```
gcc -c -o main.o main.c
gcc -c -o foo.o foo.c
gcc -c -o bar.o bar.c

gcc -o app.out main.o foo.o bar.o
```

# 빌드 규칙 블록

```makefile
<Target>: <Dependencies>
    <Recipe>
```
-   **Target:** 빌드 대상 이름 - 이 Rule에서 최종적으로 생성해내는 파일명
-   **Dependencies:** 빌드 대상이 의존하는 Target이나 파일 목록. 
	여기에 나열된 대상들을 먼저 만들고 빌드 대상을 생성합니다.
-   **Recipe:** 빌드 대상을 생성하는 명령. 
	여러 줄로 작성할 수 있으며,<font color="#00b050"> 각 줄 시작에 반드시 Tab문자로 된 Indent가 있어야 합니다.</font>
	Dependency 의존 관계에 정의된 파일의 내용이 바뀌었거나, 
	Target 대상 파일이 없을 때 
	차례대로 실행합니다. 

# 변수

### 내장 변수들
-   **CC:** 컴파일러
-   **CFLAGS:** 컴파일 옵션
-   **OBJS:** 중간 산물 Object 파일 목록
-   **TARGET:** 빌드 대상(실행 파일) 이름
-   **LDFLAGS:** 링커 옵션
-   **LDLIBS:** 링크 라이브러리

### mkdir -p
중간 디렉토리 자동생성

### 자동 변수들(automatic variables)
-   **$@:** 현재 Target 이름
-   **$^:** 현재 Target이 의존하는 대상들의 전체 목록
-   **$?:** 현재 Target이 의존하는 대상들 중 변경된 것들의 목록


# 예제
```makefile
CC = gcc
CF
```



# 메. 꾸
https://velog.io/@joonpark/Makefile-%EA%BE%B8%EB%AF%B8%EA%B8%B0


[[gcc compiler]]