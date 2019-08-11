#include "msh.h"

static int				is_special(char ch)
{
	if (ch == '\n' || ch == '\'' || ch == '\"'\
			|| ch == '\\' || ch == ' ' || ch == '$'\
			|| ch == '\t')
		return (1);
	return (0);
}

void			ex_tokens_expans_dsign(char **line, int *i, char **token)
{
	int			j;
	char		var_name[NAME_MAX + 1];
	char		*var_value;

	j = 0;
	ft_bzero(var_name, NAME_MAX + 1);
	while ((*(++*line)) && !is_special(**line) && j < NAME_MAX)
		var_name[j++] = **line;
	if ((var_value = find_var(g_msh->var, var_name)))
		append_str(token, i, var_value);
	else if ((var_value = find_var(g_msh->env, var_name)))
		append_str(token, i, var_value);
}

void			ex_tokens_expans_tild(char **line, int *i, char **token)
{
	if (*(*line + 1) == '+')
		append_str(token, i, find_var(g_msh->env, "PWD"));
	else if (*(*line + 1) == '-')
		append_str(token, i, find_var(g_msh->env, "OLDPWD"));
	else
		append_str(token, i, find_var(g_msh->env, "HOME"));
	if (*(*line + 1) == '+' || *(*line + 1) == '-')
		(*line)++;
}

void			ex_tokens_expans(char **line, int *i, char **token)
{
	if (**line == '~')
		ex_tokens_expans_tild(line, i, token);
	while (**line == '$')
		ex_tokens_expans_dsign(line, i, token);
}
