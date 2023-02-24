# instructions

-   C / norm check
-   Your functions should not quit unexpectedly (segmentation fault, bus error, double free, etc)
-   no leaks
-   If needed : makefile with `-wall -wextra -werror`
    -   use CC
    -   at leat contain : `$(NAME), all, clean, fclean and re.`
    -   `bonus` will add all the various headers/lib/func/etc forbidden on the main part of the project. `_bonus.{c/h}` if the subject specify anything else
-   **Test Enough**

size_t 에서의 문제

## part 1
memory - [[memcmp]]

## part 2
[[ft_substr]]
[[split]]














## [ft_isascii] 아스키에서 127 포함하는가? yes

The isascii() function tests for an ASCII character, which is any charac- ter between 0 and octal 0177 **inclusive.** 포함합니다




# 1. Libc functions

~~• isalpha • isdigit~~ ~~• isalnum~~ ~~• isascii~~ ~~• isprint~~ ~~• strlen~~ memset : write len of value c(converted to unsigned char) to string b / void * return/ return b • memcpy • memmove • memchr • memcmp • bzero • strlcpy • strlcat ~~• toupper • tolower~~ • strchr • strrchr ~~• strncmp~~ • strnstr • atoi

```c
void *memset(void *b, int c, size_t len);
```

### strlen : 반환형이 size_t일때의 문제

[size_t in return value](https://www.notion.so/size_t-in-return-value-e6d6a66abe974a7b927dfa0febbb3c5d)

-   32비트의 경우 부호 없는 32비트 정수(unsigned int)
    
-   64비트의 경우 부호 없는 64비트 정수(unsigned long long)을 사용하게 된다
    
    결국 size_t는 환경에 따라 달라지기 때문에, 단순 int를 쓰는 건 해결책이 아니라고 판단
    

1.  `return (sizeof(i) / sizeod(int));`
    
    문제 - 4바이트로 나누기 때문에 큰 의미가 없어짐
    
2.  gcc 기반, long의 경우 size_t와 32비트 64비트 환경에서의 크기가 동일하다. 리턴을 unsigned long으로 해 봐야지! [](https://www.ibm.com/docs/en/zos/2.3.0?topic=environments-ilp32-lp64-data-models-data-type-sizes)[https://www.ibm.com/docs/en/zos/2.3.0?topic=environments-ilp32-lp64-data-models-data-type-sizes](https://www.ibm.com/docs/en/zos/2.3.0?topic=environments-ilp32-lp64-data-models-data-type-sizes)
    

-   [ ] 나중에 크기 비교 필요

### memset

```c
void *memset(void *b, int c, size_t len);
```

writes len bytes of value c (converted to an unsigned char) to the string b.

returns its first argument

-   how to check void *b size - if len exceeds? 실제 함수 테스트시, 5사이즈에 7을 넘었을 때 오류가 나왔다. 일단은 내가 한 걸로도 오류 날 테니까.. 주어진 len이 b에 할당된 크기를 넘어서는 경우는 고려하지 않기로 한다…

![Screen Shot 2022-11-08 at 10.05.00 PM.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/ed52c485-b2fb-4af9-9caa-ee8378da8bc4/Screen_Shot_2022-11-08_at_10.05.00_PM.png)

-   할당 실패해버리기~ b에 값을 넣었을 때 void에 할당 불가
    
    [void type assign](https://www.notion.so/void-type-assign-95b377a42c4e48278ee18f16d82bda01)
    

### memcpy

```c
void *memcpy(void *restrict dst, const void *restrict src, size_t n);
```

### memmove

```c
void * memmove(void *dst, const void *src, size_t len);
```

copies len bytes from string src to string dst. The two strings may overlap; the copy is always done in a non-destructive manner.

return : dst original value

-   strncpy와 다른 점: 기본형이 str이 아님. 널종료로 체크하지 않으며, len까지만 하면 됨.
-   dst src 겹칠 경우, dst가 뒤에 있으면 반복될 수 있다. 해결책 : 주소값을 비교해서 dst 주소값이 더 클 경우, 뒤에서부터 복사한다 해결책 참조 : [](https://hand-over.tistory.com/47)[https://hand-over.tistory.com/47](https://hand-over.tistory.com/47)

![Screen Shot 2022-11-09 at 1.03.17 AM.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/e0285194-3336-4bbf-9d55-9e68be4de1ad/Screen_Shot_2022-11-09_at_1.03.17_AM.png)

[](https://hand-over.tistory.com/47)[https://hand-over.tistory.com/47](https://hand-over.tistory.com/47)

-   **복사가 이상하게 되는 경우**
    
    ![Screen Shot 2022-11-09 at 11.52.19 PM.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/54adc414-124a-4765-a8f8-3f7333bc72fc/Screen_Shot_2022-11-09_at_11.52.19_PM.png)
    
    처음에는 이렇게 나오는 게 맞는데
    
    ![Screen Shot 2022-11-09 at 11.53.34 PM.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/36b5f2ee-6428-4436-8e0b-eb3f505a20ad/Screen_Shot_2022-11-09_at_11.53.34_PM.png)
    
    그다음에 이거..?
    
    문제는 void * 일때 보이드 포인터끼리 값을 할당하는게 불가하다고 나와서 int 포인터로 캐스팅해서 썼는데
    
    그러면서 char 타입이 한번에 4개씩 복사가 된 것^^…
    
    어짜피 바이트 단위 복사이기 때문에 char로 캐스팅해도 상관없다고 판단함!
    
    ![Screen Shot 2022-11-09 at 11.53.52 PM.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/4b01e8f8-e062-408b-85e5-21ad7dffcced/Screen_Shot_2022-11-09_at_11.53.52_PM.png)
    
    ### memcmp
    
    n 바이트까지 비교 후