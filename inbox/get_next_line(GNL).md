 > 호출 반복이 될 때 한 줄씩 읽어서 반환하는 함수 구현하기.
> 
> 문제  의도  추측 : printf에서 하지 않았던 버퍼 구현하기. 파일 디스크립터의 작동 이해하기. 함수 내에서 여러 파일을 읽을 경우에 

## 파일 구성
- get_next_line.c : main func.
- get_next_line_utils.c : helper functions
- get_next_line.h - stdlib / unistd

## 조건
- return : line that was read.
	ex 1. nothing else to read
	ex 2. error occur - malloc error, NULL return
- exturnal functs. : read, malloc, free

## 주의사항
- include \n : except file ends without \n
- ==-D BUFFER_SIZE=n== add It will define the buffer size for read() / it will be modified
	-D name=definition
	The contents of definition are tokenized and processed as if they appeared during translation phase three in a ‘#define’ directive. In particular, the definition is truncated by embedded newline characters.
-  _We consider that `get_next_line` has undefined behavior if, between two calls, the same file descriptor switches to a different file before reading everything from the first fd._
    
    만약 동일한 파일 디스크립터의 두 호출 사이에서, 첫 번째 fd에서 EOF에 도달하기 전에 다른 파일로 전환될 경우, 우리는 `get_next_line`이 정의되지 않은 동작을 가진다고 생각합니다.
    
-   _Finally we consider that `get_next_line` has undefined behavior when reading from a binary file. However, if you wish, you can make this behavior coherent._
    
    마지막으로 `get_next_line`은 바이너리 파일을 읽을 때 정의되지 않은 동작을 가진다고 생각하셔야 합니다. 그러나 여러분이 원한다면 이러한 동작을 논리적으로 구현하셔도 됩니다.

- Gloval Variable : forbidden
- lseek : forbidden - file reading must be done only once.
- `-D BUFFER_SIZE` 옵션  없이도  작동해야 함. > 미지정시 기본 값필요함
- 바이너리 파일 읽을 경우 행위 미지정
- 
## 참고사항
### static variable [[variable]]
자동 변수는 콜 스택서 할당/ 해제되지만, 정적 변수는 힙 메모리에 저장
따로 초기화하지 않을 경우 0
둘다 프로그램 런타임 동안 유지되지만 
전역변수는 파일 밖에서도 선언 후 사용 가능
정적변수는 파일 안에서만 사용 가능
### Dangling Point( == premature free)
해제된 메모리 영역을 가리키는 포인터
댕글링 포인터가 가리키는 포인터는 더는 유효하지 않다
- 메모리 해제 후 포인터를 NULL로 작성
	널로 설정한 포인터를 그 이후에 사용시 프로그램 종료됨. 그러나 포인터에 대한 복사본 존재시 문제는 여전히 발생함. 여전히 댕글링 포인터 존재.
- free 함수를 대체할 새로운 함수 작성
- 해제된 메모리에 따라 특별한 값을 사용하기 - 이 값을 확인하여 해제된 메모리에 접근 확인

## 보너스
- 정적변수 1개만 선언
- 여러 개의 파일 디스크립터 관리하기


아이디어 정리
- 정적 구조체를 선언, 정적 구조체 안에는 라인, 이 라인이 나갔는지, 안 나갔는지 포함
	- 첫번째를 정적 선언하고 나머지를 말록할 경우, 나머지는 

chk_head
- static pointer head 선언 
- 이후 fd에 따라 line head를 찾아서 해당 line 반환
- 없을 경우 init, 오류시 할당 해제 후 말록 반환

	init_head
	- pointer head가 없을 경우 
	- pointer head, head, tail, head->node 생성
	- head->fd = fd 초기화
	- ==line->num = 0 초기화== 아직 미정
	

free_all(pointer head)
- 현재까지 생성된 모든 것을 반환

## pesudo code
정적 변수 : hhead (파일 디스크립터를 포함하는 리스트) 
hhead 
	head : fd 별 열어둔 파일 디스크립터를 저장.
		fd
		next(head)
		node : 파일 디스크립터에서 읽어낸 라인을 저장하는 리스트 노드.
			line : 읽어낸 라인
			num(check eof & out) : eof 감지시 -1, 내보냄 0, 안내보냄 1. 미완 2. 초기화 2.
			next(node)

함수 실행 시 fd를 받는다.
	이미 열린 파일 디스크립터인지 확인한다.
			hhead가 없을 경우 새로 생성한다.
		열려 있을 경우 : 해당 line을 찾아 반환한다
		닫혀 있을 경우 : 파일 디스크립터를 새로 열고, hhead에 저장한다. 저장된 새로운 head를 반환한다.
	파일 디스크립터 노드가 미생성시(말록 할당 실패): 널리턴
	새로운 라인이 있는지 탐색 : head 받아서 돌리면서 확인
		head 내 node를 순환, node->num 확인
		get_last_node : 마지막 노드 반환
		if
			num : -1 : eof, return stop
				close fd
				return 0
			num : 0  *eof는 아니지만 읽은 건 다 보냈음* 
				make_newline
					while (read_num == buffer)
							if  buf contains n : 
								get_newline & return newline
									node->num = 1
									node->line = newline
									node-> next = 0 
							else
								new node : realloc and alloc buf to newline
					while end : read_num buffer가 다르므로 eof 도달
						get_newline & return newline
							node->num = 0
							node->line = newline
							node-> next = 0 
			num : 2 : get newline, continue
				read add_line : num == 2 || 
					read - buffer size만큼, while - \n appears
					make_newline
			num == 1 
				: return node->line


다시
- 오류가 나는데 어디서 나는지 모르겠다
- 타임아웃 난다....

처음 생각한 글 코드
메인 : 오픈된 fd를 건넬 것이라고 가정, 말록된 메모리를 받음
겟넥라(fd) : 
	fd  / 버퍼사이즈 유효성 확인
	버퍼 없을 경우 : 버퍼 사이즈 + 1만큼 말록, 공간 할당
		널리턴확인
	라인 = 리드라인 : 읽고 반환하는 함수, static index(어디까지 갔는지) 확인
		만약 버프[인덱스] == \0 && 인덱스 = 버퍼 사이즈
			eof, 리턴 널
	라인 널리턴 확인 안함 : 만약 널이라도 eof라서...
	버프[인덱스] == 널 : 다 내보냈다고 판단하기 때문에 
		프리 후 댕글링방지(널)
	리턴 라인



# mende file
### get_next_line_utils.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:53:00 by siwolee           #+#    #+#             */
/*   Updated: 2022/12/08 23:21:16 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	chk_n_idx(char *buf)
{
	size_t	i;

	i = 0;
	if (!buf)
		return (0);
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		return (i);
	return (-1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	strsize;

	strsize = ft_strlen(s);
	if (len + start > strsize && start <= strsize)
		len = strsize - start;
	if (strsize == 0 || start >= strsize)
	{
		ptr = (char *)ft_calloc(1, 1);
		if (!ptr)
			return (0);
		return (ptr);
	}
	ptr = ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (0);
	ft_strncat(ptr, s + start, len + 1);
	return (ptr);
}

char	*read_line(char **buf, int fd)
{
	int		read_num;
	char	*line;

	line = NULL;
	if (!(*buf))
		return (line);
	read_num = 1;
	while (read_num > 0)
	{
		line = new_line(buf, line);
		if (chk_n_idx(line) >= 0) // 여기서 n idx 가 0인 것과 아닌 걸 구분 못해줬었음
			return (line);
		if (!ft_strlen(*buf))
			read_num = read(fd, *buf, (size_t)BUFFER_SIZE);
		if (read_num == -1 || (!read_num && ft_strlen(line) == 0))
		{
			free(line);
			line = 0;
		}
	}
	free(*buf);
	*buf = NULL;
	return (line);
}

char	*new_line(char **buf, char *line)
{
	size_t	b_idx;
	size_t	l_idx;
	char	*newline;

	if (!*buf)
		return (line);
	b_idx = 0;
	while ((*buf)[b_idx] && (*buf)[b_idx] != '\n')
		b_idx++;
	if ((*buf)[b_idx] == '\n')
		b_idx++;
	l_idx = 0;
	while (line && line[l_idx])
		l_idx++;
	newline = ft_calloc(b_idx + l_idx + 1, sizeof(char));
	if (!newline)
		return (0);
	ft_strncat(newline, line, l_idx + 1);
	ft_strncat(newline, *buf, b_idx + 1);
	free(line); //이거 안해줬었음
	*buf = split_buf(buf, b_idx);
	return (newline);
}

char	*split_buf(char **buf, size_t b_idx)
{
	char	*newbuf;

	if ((*buf)[b_idx] == 0)
	{
		newbuf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	}
	else
	{
		newbuf = ft_substr(*buf, b_idx, BUFFER_SIZE);
	}
	free(*buf);
	return (newbuf);
}

```
### get_next_line.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:53:00 by siwolee           #+#    #+#             */
/*   Updated: 2022/12/08 23:06:05 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	line = 0;
	if (!buf)
		buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (0);
	line = read_line(&buf, fd);
	return (line);
}

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s && s[size])
		size++;
	return (size);
}

size_t	ft_strncat(char *dst, const char *src, size_t srcsize)
{
	size_t	d_len;
	size_t	s_len;
	size_t	idx;

	d_len = 0;
	s_len = 0;
	idx = -1;
	if (!src)
		return (0);
	while (dst[d_len])
		d_len++;
	while (src[s_len])
		s_len++;
	while (src[++idx] && idx < srcsize - 1)
		dst[d_len + idx] = src[idx];
	dst[d_len + idx] = 0;
	return (d_len + s_len);
}

void	ft_bzero(void *s, size_t n)
{
	while (n)
	{
		*(char *)s = 0;
		n--;
		s++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, count * size);
	return (ptr);
}

```
### get_next_line.h
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:58:34 by haecho            #+#    #+#             */
/*   Updated: 2022/12/08 23:07:00 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifdef BUFFER_SIZE

# else
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	int		fd;
	char	*buf;
	int		idx;
}			t_list;

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *s);
size_t		ft_strncat(char *dst, const char *src, size_t srcsize);

int			chk_n_idx(char *buf);
char		*get_next_line(int fd);
char		*read_line(char **buf, int fd);
char		*new_line(char **buf, char *line);
char		*split_buf(char **buf, size_t b_idx);

#endif
```

# 문제해결
## heap-buffer-overflow
메모리 액세스가 힙 할당 개체의 범위 밖에서 발생할 때 발생하는 오류


