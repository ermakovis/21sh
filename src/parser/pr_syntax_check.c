#include "msh.h"

int			pr_syntax_check_redirect(t_list *list)
{
	t_token	*token;

	token = list->content;
	if (token->token_type != REDIRECT)
		return (SUCCESS);
	token = list->next->content;
	if (token->token_type != WORD)
	{
		ft_printf("%s: syntax error near unexpected token `%s'\n",\
			g_msh->shell_name, token->line);
		return (FAILURE);
	}
	return (SUCCESS);
}

int			pr_syntax_check(void)
{
	t_list	*list;

	list = g_msh->tokens;
	while (list)
	{
		if (pr_syntax_check_redirect(list) == FAILURE)
			return (FAILURE);
		list = list->next;
	}
	return (SUCCESS);

}
