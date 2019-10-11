#include "msh.h"

static int	bin_alias_checkname(char *line)
{
	if (!line || !*line)
	{
		ft_dprintf(2, "%s: alias: empty alias name\n", g_msh->shell_name);
		return (BIN_FAILURE);
	}
	while (*line)
	{
		if (ft_isalnum(*line) || *line == '_' || *line == '@'\
				|| *line == '%' || *line == ',')
			line++;
		else
		{
			ft_dprintf(2, "%s: alias: incorrect alias name\n",\
					g_msh->shell_name);
			return (BIN_FAILURE);
		}
	}
	return (BIN_SUCCESS);
}

static int	bin_alias_add(char *line)
{
	int		eq_pos;
	char	*value_line;

	eq_pos = ft_strclen(line, "=") - 1;
	line[eq_pos] = 0;
	if (bin_alias_checkname(line) == BIN_FAILURE)
		return (BIN_FAILURE);
	value_line = ft_strdup(line + eq_pos + 1);
	if (*value_line == '\"' || *value_line == '\'')
	{
		value_line[ft_strlen(value_line) - 1] = 0;
		ft_memmove(value_line, value_line + 1, ft_strlen(value_line));
	}
	if (find_var(g_msh->alias, line))
		set_var(g_msh->alias, line, value_line);
	else
		add_var(line, value_line, &g_msh->alias);
	ft_strdel(&value_line);
	return (BIN_SUCCESS);
}

static int	bin_alias_print(char *line)
{
	char	*value;

	if (!(value = find_var(g_msh->alias, line)))
	{
		ft_dprintf(2, "%s: alias: %s: not found\n", g_msh->shell_name, line);
		return (BIN_FAILURE);
	}
	ft_printf("%s=`%s'\n", line, value);
	return(BIN_SUCCESS);
}

int			bin_alias_action(char *line)
{
	if (ft_strchr(line, '='))
	{
		if (bin_alias_add(line) == BIN_FAILURE)
			return (BIN_FAILURE);
	}
	else if (bin_alias_print(line) == BIN_FAILURE);
		return (BIN_FAILURE);
	return (BIN_SUCCESS);
}

int			bin_alias(t_list *list)
{
	size_t	tokens_count;
	char	**tokens;
	int		i;
	int		ret;

	ret = BIN_SUCCESS;
	tokens_count = ft_lstsize(list);
	if (tokens_count == 1)
	{
		ft_lstiter(g_msh->alias, &print_var);
		return (ret);
	}
	i = 0;
	ex_tokens(&tokens, list);
	while(tokens[++i])
	{
		if (bin_alias_action(tokens[i]) == BIN_FAILURE)
			ret = BIN_FAILURE;
	}
	ft_free_table(&tokens);
	return (ret);
}
