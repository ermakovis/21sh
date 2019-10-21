#include "msh.h"

static int	ex_expansions_param_skip_squote(char **new, char *line)
{
	size_t	i;

	i = 0;
	append_char(new, '\'', NAME_MAX);
	while (line[i] != '\'')
		append_char(new, line[i++], NAME_MAX);
	append_char(new, line[i++], NAME_MAX);
	return (i);
}

static int	ex_expansions_param_skip_bslash(char **new, char *line)
{
	size_t	i;

	i = 0;
	append_char(new, '\\', NAME_MAX);
	append_char(new, line[i++], NAME_MAX);
	return (i);
}

void		ex_expansions_param(char **line)
{
	char	*new;
	char	*tmp_line;
	size_t	dquote;
	size_t	i;


	if (!ft_strchr(*line, '$'))	
		return ;
	if (!(new = ft_strnew(NAME_MAX)))
		cleanup(-1, "Malloc failed at ex_expansions_param");
	i = 0;
	dquote = 0;
	tmp_line = *line;
	while (tmp_line[i])
	{
		if (tmp_line[i] == '\"')
			dquote ^= 1;
		if (tmp_line[i] == '\\')
			i += ex_expansions_param_skip_bslash(&new, &(tmp_line[++i]));
		else if (tmp_line[i] == '\'' && !dquote)
			i += ex_expansions_param_skip_squote(&new, &(tmp_line[++i]));
		else if (tmp_line[i] == '$')
			i += ex_expansions_param_replace(&new, &(tmp_line[++i]));
		else
			append_char(&new, tmp_line[i++], NAME_MAX);
	}
	ft_memdel((void**)line);
	*line = new;
}
