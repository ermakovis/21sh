#include "msh.h" 

static int bin_export_varcmp(t_var *var1, t_var *var2)
{
	return (ft_strcmp(var1->name, var2->name));
}

static void	bin_export_printfull(void)
{
	t_list	*list;
	t_var	*var;

	ft_lst_sort(&g_msh->env, &bin_export_varcmp);
	list = g_msh->env;
	while (list)
	{
		var = list->content;
		ft_printf("export %s", var->name);
		if (var->value)
			ft_printf("=\"%s\"", var->value);
		ft_printf("\n");
		list = list->next;
	}
}

static void	bin_export_addvar(char *name, char *value)
{
	if (find_var(g_msh->env, name))
		set_var(g_msh->env, name, value);
	else
		add_var(name, value, &g_msh->env);
}

static void	bin_export_assign(char **tokens)
{
	int		i;
	int		eq_pos;
	char	*value;

	i = -1;

	while (tokens[++i])
	{
		if (!ft_strchr(tokens[i], '='))
		{
			if ((value = find_var(g_msh->var, tokens[i])))
				bin_export_addvar(tokens[i], value);
			continue ;
		}
		eq_pos = ft_strclen(tokens[i], "=") - 1;
		tokens[i][eq_pos] = 0;
		bin_export_addvar(tokens[i], tokens[i] + eq_pos + 1);
	}
}

int		bin_export(t_list *list)
{
	char	**tokens;
	int		i;
	int		ret;

	ret = BIN_SUCCESS;
	ex_tokens(&tokens, list);
	if (!tokens[1] || !ft_strcmp(tokens[1], "-p"))
		bin_export_printfull();
	else
		bin_export_assign(&tokens[1]);
	ft_free_table(&tokens);
	return (ret);
}


