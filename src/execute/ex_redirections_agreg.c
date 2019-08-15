#include "msh.h"

void		ex_redirections_agreg_more(char *redir, char *word)
{
	int		num;

	if (ft_isdigit(*redir))
		num = atoi(redir);
	else
		num = 1;
	if (ft_isnumber(word))
		dup2(ft_atoi(word), num);
	else if (ft_strequ(word, "-"))
		close(num);
}

void		ex_redirections_agreg_less(char *redir, char *word)
{
	int		num;

	if (ft_isdigit(*redir))
		num = atoi(redir);
	else
		num = 0;
	if (ft_isnumber(word))
		dup2(ft_atoi(word), num);
	else if (ft_strequ(word, "-"))
		close(num);
}

void		ex_redirections_agreg(t_list *list)
{
	t_token		*token;
	char		*word;

	token = list->content;
	word = ((t_token*)list->next->content)->line;
	if (token->operator_type == MORE_AND)
		return (ex_redirections_agreg_more(token->line, word));
	else if (token->operator_type == LESS_AND)
		return (ex_redirections_agreg_less(token->line, word));
}

