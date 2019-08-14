#include "msh.h"

void		ex_redirections_simple_more(char *redir, char *word)
{
	int		num;
	int		fd;

	if (ft_isdigit(*redir))
		num = atoi(redir);
	else
		num = 1;
	fd = open(word, O_RDWR | O_CREAT | O_TRUNC, 0666);
	dup2(fd, num);
}

void		ex_redirections_simple_dmore(char *redir, char *word)
{
	int		num;
	int		fd;

	if (ft_isdigit(*redir))
		num = atoi(redir);
	else
		num = 1;
	fd = open(word, O_RDWR | O_CREAT | O_APPEND, 0666);
	dup2(fd, num);
}

void		ex_redirections_simple_less(char *redir, char *word)
{
	int		num;
	int		fd;

	if (ft_isdigit(*redir))
		num = atoi(redir);
	else
		num = 0;
	fd = open(word, O_RDONLY);
	dup2(fd, num);
}
void		ex_redirections_simple(t_list *list)
{
	t_token		*token;
	char		*word;

	token = list->content;
	word = ((t_token*)list->next->content)->line;
	if (token->operator_type == MORE)
		return (ex_redirections_simple_more(token->line, word));
	else if (token->operator_type == DMORE)
		return (ex_redirections_simple_dmore(token->line, word));
	else if (token->operator_type == LESS)
		return (ex_redirections_simple_less(token->line, word));
}
