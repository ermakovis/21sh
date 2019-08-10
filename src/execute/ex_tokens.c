#include "msh.h"

static char			*ex_tokens_expand(t_token *token)
{
	return (ft_strdup(token->line));
}

void			ex_tokens(t_ast *ast, char ***tokens)
{
	t_list	*list;
	char	**ret;
	int		i;
	size_t	size;

	i = 0;
	list = ast->token;
	size = ft_lstsize(list) + 1;
	if (!(ret = (char**)malloc(sizeof(char*) * size)))
		cleanup(-1, "Malloc failed at ex_command_tokens");
	ft_bzero(ret, sizeof(char*) * size);
	while (list)
	{
		ret[i++] = ex_tokens_expand(list->content);
		list = list->next;;
	}
	*tokens = ret;
}
