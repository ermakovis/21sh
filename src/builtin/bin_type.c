#include "msh.h"

static int	bin_type_cycle(char *line)
{
	t_list	*list;
	int		ret;

	ret = BIN_FAILURE;
	if ((list = ft_lst_find(g_msh->alias, line, &cmp_var)))
	{
		ft_printf("%s is aliased to `%s'\n", line,\
			((t_var*)list->content)->value);
		ret = BIN_SUCCESS;
	}
	else if ((list = ft_lst_find(g_msh->bin, line, &cmp_bins)))
	{
		ft_printf("%s is a shell builtin\n", line);
		ret = BIN_SUCCESS;
	}
	else if ((list = ft_lst_find(g_msh->hash, line, &cmp_hash)))
	{
		ft_printf("%s is %s\n", line, ((t_hash*)list->content)->command);
		ret = BIN_SUCCESS;
	}
	else
		ft_dprintf(2, "%s: type: %s: not found\n", g_msh->shell_name, line);
	return (ret);
}

int			bin_type(t_list *list)
{
	char	**tokens;
	int		i;
	int		ret;

	i = 0;
	ret = BIN_SUCCESS;
	ex_tokens(&tokens, list);
	while (tokens[++i])
		if ((ret = bin_type_cycle(tokens[i])) == BIN_FAILURE)
			ret = BIN_FAILURE;
	ft_free_table(&tokens);
	return (ret);
}
