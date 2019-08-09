#include "msh.h"

static int		lch_launch_check_executable(char *path)
{
	if (!ft_test_path(path))
	{
		ft_dprintf(2, "%s: command not found\n", path);
		return (0);
	}
	if (!(ft_test_path(path) & 1))
	{
		ft_dprintf(2, "%s: permission denied\n", path);
		return (0);
	}
	return (1);
}

static int		lch_launch_execute(t_list *list)
{
	int		pid;
	t_lch	*lch;
	char	**tokens;

	lch = list->content;
	tokens = lch->tokens;
	if (!lch_launch_check_executable(tokens[0]))
		return (0);
	if ((pid = fork()) == -1)
		ft_printf("%s: fork failed\n", tokens[0]);
	else if (pid == 0)
	{
		lch_launch_dups(list);
		lch_launch_closes();
		if (execve(tokens[0], tokens,lch->env) < 0)
			ft_dprintf(2, "%s: launch failed\n", tokens[0]);
		exit(-1);
	}
	return (1);
}

static void		lch_launch_pop_used(void)
{
	t_lch	*lch;
	char	separator;

	while (g_msh->lch)
	{
		lch = g_msh->lch->content;	
		separator = lch->separator;
		ft_lstpop(&g_msh->lch, &del_lch);
		if (separator != '|')
			return ;
	}
}

static void		lch_launch_pipe_loop(void)
{
	t_list	*list;
	t_lch	*lch;
	int		i;
	int		status;

	i = 0;
	list = g_msh->lch;
	while (list)
	{
		i++;
		if (!lch_check_bins(list))
			if (!lch_launch_execute(list))
				break ;
		if ((lch = list->content)->separator != '|')
			break ;
		list = list->next;
	}
	lch_launch_closes();
	while(i--)
		wait(&status);
}

void	lch_launch(void)
{
	if (!g_msh->lch || !g_msh->lch->content)
		return ;
	lch_create_pipes();
	lch_launch_pipe_loop();
	lch_launch_pop_used();
	lch_launch();
}
