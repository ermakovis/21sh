#include "msh.h"

static void		ex_rd_heredoc_getline(t_list *list, char **line)
{
	char	*tmp;
	char	*word;
	char	*rl_line;
	size_t	line_len;

	*line = NULL;
	cl_rl_struct();
	word = ((t_token*)list->next->content)->line;
	while (read_line())
	{
		rl_line = g_msh->rl->line;
		line_len = ft_strlen(rl_line);
		rl_line[line_len - 1] = 0;
		if (ft_strequ(rl_line, word))
			break ;
		rl_line[line_len - 1] = '\n';
		tmp = *line;
		if (!(*line = ft_strjoin(*line, rl_line)))
			cleanup(-1, "Malloc failed at heredoc_getline");
		ft_memdel((void**)&tmp);
		cl_rl_struct();
	}
}

static void	ex_rd_heredoc_pipe(int num, char *line)
{
	int		fd[2];

	if (pipe(fd) == -1)
		return ;
	write(fd[1], line, ft_strlen(line));
	close(fd[1]);
	dup2(fd[0], num);
	close(fd[0]);
}

static void		ex_rd_heredoc_getnum(t_list *list, int *num)
{
	t_token		*token;

	token = list->content;
	if (ft_isdigit(token->line[0]))
		*num = ft_atoi(token->line);
	else
		*num = 0;
}

void		ex_redirections_heredoc(t_list *list)
{
	t_token *token;
	char	*line;
	int		num;

	line = NULL;
	num = 0;
	while (list)
	{
		token = list->content;
		if (token->token_type == REDIRECT && token->operator_type == DLESS)
		{
			ft_memdel((void**)&line);
			ex_rd_heredoc_getnum(list, &num);
			ex_rd_heredoc_getline(list, &line);
		}
		list = list->next;
	}
	if (line)
		ex_rd_heredoc_pipe(num, line);
	ft_memdel((void**)&line);
}

