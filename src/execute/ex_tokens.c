#include "msh.h"

static char			*ex_tokens_switch(t_token *token)
{	
	char	*line;
	char	*ret;
	int		i;

	i = 0;
	line = token->line;
	if (!(ret = ft_strnew(MSH_BUFF_SIZE)))
		cleanup(-1, "Malloc failed at ex_tokens_expans");
	while (*line)
	{
		realloc_check(&ret, i);
		if ((*line == '~' && i == 0) || *line == '$')
			ex_tokens_expans(&line, &i, &ret);
		else if (*line == '\'' || *line == '\"' || *line == '\\')
			ex_tokens_quotes(&line, &i, &ret);
		else 
			ret[i++] = *line;
		line++;
	}
	return (ret);
}

void			ex_tokens(t_ast *ast, char ***tokens)
{
	t_list	*list;
	t_token *token;
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
		token = list->content;
		if (token->token_type == REDIRECT)
			list = list->next->next;
		else if (token->token_type == ASSIGNMENT)
			list = list->next;
		else
		{
			ret[i++] = ex_tokens_switch(list->content);
			list = list->next;
		}
	}
	*tokens = ret;
}
