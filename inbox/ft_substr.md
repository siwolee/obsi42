~~~
char *ft_substr(char const *s, unsigned int start, size_t len);

const *s :  원본 문자열 - substring을 생성할
start: 인덱스 - s에 들어있는 시작 인덱스
len: 생성할 substring의 최대 길이

리턴 : 생성 문자열 / NULL - 할당 실패시
~~~

 시작 인덱스부터 최대 len 길이를 malloc, s 에서 복사

- 만약 start ~ end 길이가 len보다 적을 경우 : 미리 체크해서 len 줄이기( 최대길이임)
- 인덱스가 unsigned int 길이 넘어갈 경우 : 의미없음... 안 들어옴

- if len == 0 
	- return "" or null  
	The C standard (C17 7.22.3/1) says:
> 	If the size of the space requested is zero, the behavior is implementation defined: either a null pointer is returned, or the behavior is as if the size were some nonzero value, except that the returned pointer shall not be used to access an object.
> 	So I choose to get **NULL**

So, `malloc(0)` could return `NULL` or a valid pointer _that may not be dereferenced_. In either case, it's perfectly valid to call `free()` on it.
- if s_string is empty


start  + len > strsize
	len = strsize- start
len == 0
	return malloc (0)
