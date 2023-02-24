`size_t` is the unsigned integer type of the result of [sizeof](https://en.cppreference.com/w/c/language/sizeof) , [_Alignof](https://en.cppreference.com/w/c/language/_Alignof) (since C11) and [offsetof](https://en.cppreference.com/w/c/types/offsetof), depending on the [data model](https://en.cppreference.com/w/c/language/arithmetic_types#Data_models)

sizeof, _Alignof의 반환형으로 해당 시스템에서 어떤 객체나 값이 포함할 수 있는 최대 크기의 데이터를 표현하는 타입

`size_t`  can store the maximum size of a theoretically possible object of any type

해당 명세에 따르면 x86은 32비트, x64는 64비트 변수가 된다.

만약 사이즈 값을 unsigned int로 줄 경우에는 운영체제마다 달라지는 값을 반영할 수 없기 때문에 size_t를 사용해서

-   32비트의 경우 부호 없는 32비트 정수(unsigned int)
-   64비트의 경우 부호 없는 64비트 정수(unsigned long long)을 사용하게 된다

[libft_strlen]

size_t strlen(const char *s);

```
 size_t
 strnlen(const char *s, size_t maxlen);

```

DESCRIPTION The strlen() function computes the length of the string s. The strnlen() function attempts to compute the length of s, but never scans beyond the first maxlen bytes of s.

RETURN VALUES The strlen() function returns the number of characters that precede the terminating NUL character. The strnlen() function returns either the same result as strlen() or maxlen, whichever is smaller.