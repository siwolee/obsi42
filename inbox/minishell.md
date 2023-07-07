# 🌈 현재 도전과제
- [x] ^ 파이프 넘겼을 때 강제 종료되는 문제
	exit 했을 때 정상종료됨, 이후 널 반
- [x] execfile정리
- [ ] cmd_not_found 여러 개 실행시 쉘 여러번 실행
- [x] 빌트인 함수인지 검사하기
- [ ] 환경변수 검사하기 > 주휴리
- [ ] 에러 목록 체크해서 헤더 만들어두기
- [x] heredoc 처리

## 파이프 넘겼을때 강제종료되는문제

```sh
MONGSHELL $ pipe | pipe
error execve
exit 0 fine, status 256
cmd not found
error execve
exit 1 fine, status 256
exit 2 fine, status 256
MONGSHELL $ cmd not found
cmd not found
error execve
exit 0 fine, status 256
exit 1 fine, status 256
```

# 🌈 현재 도전과제






```c
// int execute_init(t_node *head, t_env *env)

// {

// t_node *node;

// t_node *next;

// t_cmd *cmd;

// pid_t pid;

// char **path;

// int res;

  

// cmd = init_cmd();

// path = get_path(env);

// node = head->next;

// signal(SIGINT, SIG_IGN);

// signal(SIGQUIT, SIG_IGN);

// while (node)

// {

// next = parse_node_to_cmd_parent(node, cmd);

// chk_builtin(cmd, env);

// if (pid == -1)

// throw_error("fork error", 1);

// pid = fork();

// if (!pid)

// {

// signal(SIGINT, SIG_DFL);

// signal(SIGQUIT, SIG_DFL);

// parse_node_to_cmd_child(node, cmd);

// char *full_cmd;

// full_cmd = get_full_cmd(cmd, path);

// if (!(full_cmd))

// child_exit("cmd not found", 127);

// chk_pipe_child(cmd);

// if (execve(full_cmd, cmd->argv, NULL) == -1)

// child_exit("error execve", 1);

// else

// exit(0);

// }

// else

// {

// ft_putnbr_fd((int)pid, STDOUT_BU);

// reset_pipe_parent(cmd);

// }

// node = next;

// if (node)

// node = node->next;

// }

// res = wait_all(cmd, pid, path);

// free_cmd(cmd);

// mini_lstclear(cmd->red_file);

// // printf("sdfsdfasdf\n");

// return (res);

// }

  
  

int execute_init(t_node *head, t_env *env)

{

t_node *node;

t_cmd *cmd;

pid_t pid;

char **path;

t_node *next;

  

cmd = init_cmd();

path = get_path(env);

node = head->next;

signal(SIGINT, SIG_IGN);

signal(SIGQUIT, SIG_IGN);

while (node)

{

next = parse_node_to_cmd_parent(node, cmd, path); //open file 빼고 여기서 처리

chk_builtin(cmd, env);

pid = fork();

if (!pid)

{

signal(SIGINT, SIG_DFL);

signal(SIGQUIT, SIG_DFL);

parse_node_to_cmd_child(node, cmd);// file fd열고 dup

chk_pipe_child(cmd); //pipe 열고 dup

if (execve(cmd->filename, cmd->argv, NULL) == -1)

{

ft_putendl_fd("msh: command not found", STDOUT_BU); //error // 고쳐야함

exit(1);

}

else

exit(0);

}

reset_pipe_parent(cmd, node);

node = next;

if (node)

node = node->next;

}

dup2(STDOUT_BU, 1);

dup2(STDIN_BU, 0);

return (wait_all(cmd, pid, path));

}

```


### wait - 순서를 어떻게 할 것인가?
> 
```c
int	wait_all(t_cmd *cmd, pid_t pid, char **path)
{
	int	status;
	int	i;

	i = 0;
	while (cmd->cnt -1 > i)
	{
		if (wait(&status) == -1)
		{
			ft_putnbr_fd(status, 2);
			throw_error(": msh: ", "unexit child", "", -1);
		}
		i++;
	}
	waitpid(pid, &status, 0);
	i = -1;
	while (path && path[++i])
		free(path[i]);
	free(path);
	path = 0;
	dup2(STDOUT_BU, 1);
	dup2(STDIN_BU, 0);
	free(cmd);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (WSTOPSIG(status));
}
```

cat | cat | ls 에서의 문제.
ls가 제일 먼저 종료되기 때문에, 원래대로라면 마지막waitpid에서 걸려서 나오게 설계되어 있는데
while 문 안에서 처리되어 나오게 된다....
그래서 순서를 바꿨다. 

