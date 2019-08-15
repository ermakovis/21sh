#include "msh.h"

void		ex_redirections(t_list *list)
{
	t_token		*token;

	while (list)
	{
		token = list->content;
		if (token->token_type == REDIRECT)
		{
			if (token->operator_type == LESS || token->operator_type == MORE\
				|| token->operator_type == DMORE)
				ex_redirections_simple(list);
			else if (token->operator_type == LESS_AND\
				|| token->operator_type == MORE_AND)
				ex_redirections_agreg(list);
		
		}
		list = list->next;
	}
	
	
}
