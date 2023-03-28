#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//두번째 ~ 마지막 줄로 들어오는
//각 원의 중심점(x, y), 반지름(rad)
//type c랑 C가 각각 채운 원/ 안채운 원
typedef struct s_node
{
	char	type;
	float	x;
	float	y;
	float	rad;
	char	fill;
	struct s_node *next;
} t_node;


//첫번째 줄로 들어오는 전체 길이, 높이, 
//빈 곳에 채울 char(empty)
typedef struct s_env
{
	float	wid;
	float	hei;
	char	empty;
	t_node	*node;
} t_env;

int	draw(t_env *env)
{
	float	w;
	float	h;
	char	c;

	h = 0;
	while (h < env->hei)
	{
		w = 0;
		while (w < env->wid)
		{
			node = env->node;
			c = env->empty;
			while (node)
			{
				if (get_length(node))
					c = node->fill;
				node = node->next;
			}
			write(1, c, 1);
			w++
		}
		h++;
	}
	return (0);
}

	





