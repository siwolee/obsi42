[[가변인자 인수의 사용]]

## mandatory : implementing original printf
objective
	func to implement
	int ft_printf(const char \*, ...);
external library
	stblib : malloc. free
	unistd : write
	stdarg :  va_start, va_arg, va_copy, va_end
		[[가변인자 인수의 사용]]


## 고려해야 할 점
- [x] 가변인자 확인
- [ ] 타입 별 오류
- [ ] 타입 별 포맷팅 플래그
- [ ] 이스케이프 시퀀스 (\\\*)


# 타입 별 상황별 처리
### %c : single char
- 캐릭터 하나 이상
- unprintable
- char 범위 넘어선 값
### %s : string
- /0으로 끝나지 않을 경우?
- unprintable- 따로 처리 안함
### %p : void \*  in hx
- ...
### %d : num in base 10
### %i : interger in base 10
### %u : unsigned num in base 10
### %x : num in base 16 : lowercase
### %X :  \" : uppercase
### \% : percent sign.



안희근데 대체 메인문은 따로 어떻게 만드는거임
