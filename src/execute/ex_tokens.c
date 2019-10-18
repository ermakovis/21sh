#include "msh.h"

static char *ex_env_getvalue(char *name)
{
	t_list *list;

	if (list = ft_lst_find(g_msh->cmd_var, name, &cmp_var))
		return (((t_var*)list->content)->value);
	if (list = ft_lst_find(g_msh->var, name, &cmp_var))
		return (((t_var*)list->content)->value);
	if (list = ft_lst_find(g_msh->env, name, &cmp_var))
		return (((t_var*)list->content)->value);
	return (ft_strdup("SOMETHING GONE HORRIBLY WRONG\n"));
}

void		ex_env(char ***env)
{
	t_list	*env_list;
	t_var	 *var;
	char	*value;
	char	**ret;
	int		i;

	i = 0;
	if (!(env_list = g_msh->env))
		return ;
	if (!(ret = (char**)ft_memalloc(sizeof(char*) *\
		(ft_lstsize(env_list) + 1))))
		cleanup(-1, "Malloc failed at ex_command_env");
	while (env_list)
	{
		var = env_list->content;
		value = ex_env_getvalue(var->name);
		ret[i++] = var_to_str(var->name, value);
		env_list = env_list->next;
	}
	*env = ret;
}

void		ex_tokens(char ***tokens, t_list *list)
{
	char	**ret;
	size_t	size;
	int		i;

	i = 0;
	if (!list)
		return ;
	size = ft_lstsize(list) + 1;
	if (!(ret = (char**)malloc(sizeof(char*) * size)))
		cleanup(-1, "Malloc failed at ex_command_env");
	ft_bzero(ret, sizeof(char*) * size);
	while (list)
	{
		if (((t_token*)list->content)->token_type == REDIRECT)
			list = list->next;
		else
			ret[i++] = ft_strdup(((t_token*)list->content)->line);
		list = list->next;
	}
	*tokens = ret;
}
