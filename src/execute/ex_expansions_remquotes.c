#include "msh.h"

static int	is_quote(char ch)
{
	if (ch == '\'')
		return (1);
	if (ch == '\"')
		return (1);
	if (ch == '\\')
		return (1);
	return (0);
}

void		ex_expansions_remquotes(t_token *token)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(token->line);
	while (token->line[i])
	{
		if (is_quote(token->line[i]))
		{
			ft_memmove(&token->line[i], &token->line[i + 1], len - i);
			len--;
		}
		else
			i++;
	}
}
