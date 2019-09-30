#include "msh.h"

static int	ex_expansions_param_replace(char **new, char *line)
{
	char	var_name[NAME_MAX + 1];
	char	*var_value;
	size_t	i;

	if (!*line)
	{
		append_char(new, '$', NAME_MAX);
		return (0);
	}
	i = -1;
	ft_bzero(var_name, NAME_MAX + 1);
	while (line[++i] && !is_special(line[i]) && i < NAME_MAX)
		var_name[i] = line[i];
	if ((var_value = find_var(g_msh->var, var_name)))
		append_line(new, var_value, NAME_MAX);
	else if ((var_value = find_var(g_msh->env, var_name)))
		append_line(new, var_value, NAME_MAX);
	return (i);
}

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

void		ex_expansions_param(t_token *token)
{
	char	*new;
	size_t	dquote;
	size_t	i;

	if (!ft_strchr(token->line, '$'))	
		return ;
	if (!(new = ft_strnew(NAME_MAX)))
		cleanup(-1, "Malloc failed at ex_expansions_param");
	i = 0;
	dquote = 0;
	while (token->line[i])
	{
		if (token->line[i] == '\"')
			dquote ^= 1;
		if (token->line[i] == '\\')
			i += ex_expansions_param_skip_bslash(&new, &(token->line[++i]));
		else if (token->line[i] == '\'' && !dquote)
			i += ex_expansions_param_skip_squote(&new, &(token->line[++i]));
		else if (token->line[i] == '$')
			i += ex_expansions_param_replace(&new, &(token->line[++i]));
		else
			append_char(&new, token->line[i++], NAME_MAX);
	}
	ft_memdel((void**)&token->line);
	token->line = new;
}
