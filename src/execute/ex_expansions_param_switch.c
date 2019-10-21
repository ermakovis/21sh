#include "msh.h"

static void ex_expansions_param_number(char *param, char **new)
{
	t_list	*list;
	char	*line;
	char	*itoa_line;
	int		len;
	
	line = 0;
	if ((list = ft_lst_find(g_msh->var, param, &cmp_var)))
		line = ((t_var*)list->content)->value;
	else if ((list = ft_lst_find(g_msh->env, param, &cmp_var)))
		line = ((t_var*)list->content)->value;
	len = ft_strlen(line);
	if (!(itoa_line = ft_itoa(len)))
		cleanup(-1, "Malloc failed at ex_expansions_param_number");
	append_line(new, itoa_line, NAME_MAX); 
	ft_memdel((void**)&itoa_line);
}

static void ex_expansions_param_simple(char *param, char **new)
{
	t_list	*list;
	char	*line;

	if ((list = ft_lst_find(g_msh->var, param, &cmp_var)))
		append_line(new, ((t_var*)list->content)->value, NAME_MAX);
	else if ((list = ft_lst_find(g_msh->env, param, &cmp_var)))
		append_line(new, ((t_var*)list->content)->value, NAME_MAX);
}

int		ex_expansions_param_switch(char *param, char *word,\
			int flags, char **new)
{
	if (flags & EXP_NUM)
		ex_expansions_param_number(param, new);
	else if (flags == 0)
		ex_expansions_param_simple(param, new);

}
