#include "msh.h"

void		ex_expansions_remquotes(t_token *token)
{
	size_t	i;
	int		squote;
	int		dquote;
	char	*line;

	i = 0;
	squote = 0;
	dquote = 0;
	line = token->line;
	while (line[i])
	{
		if (line[i] == '\\' && !squote)
		{
			ft_memmove(&line[i], &line[i + 1], ft_strlen(&line[i]));
			i++;
		}
		else if (token->line[i] == '\'' && !dquote)
		{
			ft_memmove(&line[i], &line[i + 1], ft_strlen(&line[i]));
			squote ^= 1;
		}
		else if (line[i] == '\"' && !squote)
		{
			ft_memmove(&line[i], &line[i + 1],ft_strlen(&line[i]));
			dquote ^= 1;
		}
		else
			i++;
	}
}
