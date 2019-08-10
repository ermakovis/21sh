#include "msh.h"

static int		ex_command_fork_signals(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	else
		return (FAILURE);
}

int				ex_command_fork(char *cmd, char **tokens, char **env)
{
	pid_t		pid;
	int			status;
	
	if (ex_check_executable(cmd) == FAILURE)
		return (FAILURE);
	if ((pid = fork()) == -1)
		return (FAILURE);
	if (pid == 0)
	{
		if ((status = execve(cmd, tokens, env) == -1))
			ft_dprintf(2, "%s: launch failed\n", cmd);
		exit (-1);
	}
	ft_memdel((void**)&cmd);
	wait(&status);
	return (ex_command_fork_signals(status));
}
