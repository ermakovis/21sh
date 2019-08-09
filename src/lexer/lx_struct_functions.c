#include "msh.h"

void		print_token(t_list *list)
{
	t_token *token;

	token = list->content;
	ft_printf("line - %-10s | token - %3d | operator - %3d\n",\
				token->line, token->token_type, token->operator_type);
}

void		print_token_line(t_list *list)
{
	t_token *token;

	while (list)
	{
		token = list->content;
		ft_printf("%s ", token->line);
		list = list->next;
	}
	ft_printf("\n");
}

int			add_token(char *line, int token, int operator)
{
	t_list		*new_list;
	t_token		*new;
	size_t		size;

	size = sizeof(t_token);
	if (!(new = (t_token*)malloc(size)))
		cleanup(-1, "Malloc failed at add_token");
	ft_bzero(new, size);
	if (!(new->line = ft_strdup(line)))
		cleanup(-1, "Malloc failed at add_token 1");
	new->token_type = token;
	new->operator_type = operator;
	if (!(new_list = ft_lstnew(new, size)))
		cleanup(-1, "Malloc failed at add_token 2");
	ft_memdel((void**)&new);
	ft_lstadd_last(&g_msh->tokens, new_list);
	return (ft_strlen(line));
}

void		del_token(void *content, size_t size)
{
	t_token		*token;

	if (!content)
		return;
	(void)size;
	token = content;
	ft_memdel((void**)&(token->line));
	ft_memdel((void**)&content);
}
