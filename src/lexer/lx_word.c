#include "msh.h"

static void		lx_word_add_token(char* line, int len)
{
	char save;

	save = line[len];
	line[len] =	0;
	add_token(line, WORD, NONE);
	line[len] = save;
}

/*
**	starts at 1 to ignore the first ", returns +1 to ignore the last;
*/
static int		lx_word_dquote_len(char *line)
{
	int		len;

	len = 1;
	while (line[len] && line[len] != '\"')
	{
		if (line[len] == '\\')
			len++;
		len++;
	}
	return (len + 1);
}

int				lx_word_check(char ch)
{
	if (ft_isprint(ch) && !ft_isspace(ch) && !lx_redirect_check(ch))
		return (1);
	return (0);
}

int				lx_word_get(char *line)
{
	int		len;

	len = 0;
	while (line[len] && lx_word_check(line[len]))
	{
		if (line[len] == '\\')
			len++;
		else if (line[len] == '\'')
			len += ft_strclen(&line[len + 1], "'\'") + 1;
		else if (line[len] == '\"')
			len += lx_word_dquote_len(&line[len]);
		else
			len++;
	}
	lx_word_add_token(line, len);
	return (len);
}
