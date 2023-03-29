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


//처음 초기화 및 에러처리 부분..
//공통되는 부분(전체 사이즈, 빈 공간) 은 env에, 
//그 이후 원의 정보는 env->node에 연결 리스트로 malloc
//마지막에 node만 돌면서 프리해줄 수 있게 node 내에서는 포인터를 안 쓰는 걸 추천..

//에러시 리턴 필요하므로 int 리턴하게 할 것..
int newnode(FILE file, t_node *prev)
{
	t_node	*node;
	char c;
	int i;

	while (fread(1, &c, 1)) && (c == ' ' || c == '\n')
		i++; //걍 와일문 반복..
	if (c == 0)
		return (0);// (끝난거라서 정상종료)
	else if (c != 'c' && c != 'C')
		return (1); // type 들어오지 않음 : error
	
	node = malloc(sizeof(t_node));
	if (!node)
		return (1);
	
	i = fscanf(file, "%f %f %f %c", &node->x, &node->y, &node->rad, &node->fill);
	if (i != 4)
	{
		free(node);
		return (1);
	}
	node->next = 0;
	prev->next = node;
	return (0);
}

int init_env(t_env *env)
{
	t_node *node;

	if (fscanf(file, "%f %f %c", &env->wid, &env->hei, &env->empty) != 3)
		return (1);
	if (env->wid > 300 || env->hei > 300)
		return (1); //이건 예외처린데 잘 모르겠음..
	if (env->wid <= 0 || env->hei <= 0)
		return (1); //이것도 해야 하나..
	
	node = env->node;
	while (1)
	{
		if (init_node(node))
			return (1);
		node = node->next;
		if (!node)
			break;
	}
	return (0);
}





//반지름의 길이와, 현재 위치-원의 중심 간 거리 비교
//타입 확인해서 인쇄해야 할 곳이면 1, 
//빈 곳이면 0 리턴
int	is_fill(t_node *node, float w, float h)
{
	flaot len;됨

	len = sqrtf(powf(node->x - w, 2) + powf(node->y - h, 2)); 
	//길이 =  (중심점 가로위치- 현재 가로 좌표)제곱 + (중심점 높이 - 현재 세로 좌표)제곱 
	//의 제곱근을 구한 것...
	//피타고라스... 이건 문제에 나옴...
	
	if (node->type == 'c')
	{
		if (node->rad >= len && node->rad - 1 <= len)
			return (1);
		//속이 빈 원형일 경우.. c 인지 C인지는 생각 안남
		//외곽선만 그리는 식인데 뒤에가 rad-1 <= len인지 rad-1 < len인지
		//시험장 가서 ./our_mini_paint로 뽑은 거랑
		//diff 비교해보면서 조정하면 됨 
	}
	else
	{
		if (node->rad >= len)
			return (1);
		//속이 찬 원형
	}
}
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
				if (is_fill(node))
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

int error_msg(char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
	return (1);
}
int main(int ac, char **av)
{
	FILE *file;
	t_env env;
	t_node *node;
	t_node *next;

	if (ac != 2)
		return (error_msg("dfasdlj\n"));
	if (fopen(file, av[1]) == 0)
		return (error_msg("safsdfd\n"));
	if (init_env(&env, file))
		return (error_msg("safsdfd\n"));
	
	draw(&env);

	node = env->node;
	while (node)
	{
		next = node->next;
		free(node);
		node = next;
	}
	return (0);
}






