relink 된 문제
```Makefile
LIBFT = libft.a


all : $(NAME)
// 이거 생략하고 바로 했을 경우 계속 만듬. 목적이 없이 계속 실행.

$(NAME) : $(LIBFT) $(MENDE_OBJ) $(OBJS)
	$(CC) $(CFLAGS) -L. -lft -o $(NAME) $(MENDE_OBJ) $(OBJS)
```

