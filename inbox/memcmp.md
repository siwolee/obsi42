```
#include <stdio.h>

#include <string.h>

  

int main()

{

char *s1 = "atoms\0\0\0\0";

char *s2 = "atoms\0abc";

size_t size = 8;

int i1 = memcmp(s1, s2, size);

int i2 = ft_memcmp(s1, s2, size);

  

printf("%d\n%d\n", i1, i2);

if (i1 == i2)

printf("$");

}
```



