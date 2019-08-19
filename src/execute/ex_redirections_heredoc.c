#include "msh.h"

static char		*ex_redirections_heredoc_getline(char *word)
{
	char	*ret;
	char	*tmp;
	char	*rl_line;
	size_t	line_len;

	ret = NULL;
	cl_rl_struct();
	while (read_line())
	{
		rl_line = g_msh->rl->line;
		line_len = ft_strlen(rl_line);
		rl_line[line_len - 1] = 0;
		if (ft_strequ(rl_line, word))
			break ;
		rl_line[line_len - 1] = '\n';
		tmp = ret;
		if (!(ret = ft_strjoin(ret, rl_line)))
			cleanup(-1, "Malloc failed at heredoc_getline");
		ft_memdel((void**)&tmp);
		cl_rl_struct();
	}
	return (ret);
}

static void	ex_redirections_heredoc_pipe(int num, char *line)
{
	int		fd[2];

	if (pipe(fd) == -1)
		return ;
	write(fd[1], line, ft_strlen(line));
	close(fd[1]);
	dup2(fd[0], num);
	close(fd[0]);
}

void		ex_redirections_heredoc(t_list *list)
{
	t_token		*token;
	char		*word;
	char		*heredoc_line;
	int			num;

	token = list->content;
	word = ((t_token*)list->next->content)->line;
	if (ft_isdigit(token->line[0]))
		num == ft_atoi(token->line);
	else
		num = 0;
	if (!(heredoc_line = ex_redirections_heredoc_getline(word)))
		return ;
	ex_redirections_heredoc_pipe(num, heredoc_line);
}
