#include "msh.h"

static void	ex_exp_param_usedef(char *param, char *word, char **new)
{
	char	*value;

	if ((value = ex_expansions_param_getline(param)))
		append_line(new, value, NAME_MAX);
	else
		append_line(new, word, NAME_MAX);
}

static void	ex_exp_param_useass(char *param, char *word, char **new)
{
	char	*value;

	if ((value = ex_expansions_param_getline(param)))
		append_line(new, value, NAME_MAX);
	else
	{
		if (find_var(g_msh->var, param))
			set_var(g_msh->var, param, word);
		else
			add_var(param, word, &g_msh->var);
		append_line(new, word, NAME_MAX);
	}
}

static void ex_exp_param_usealt(char *param, char *word, char **new)
{
	char *value;

	if ((value = ex_expansions_param_getline(param)))
		append_line(new, word, NAME_MAX);
}

void		ex_expansions_param_use(char *param, char *word,\
				int flags, char **new)
{
	if (flags & EXP_USEDEF)
		return (ex_exp_param_usedef(param, word, new));
	if (flags & EXP_USEASS)
		return (ex_exp_param_useass(param, word, new));
	if (flags & EXP_USEALT)
		return (ex_exp_param_usealt(param, word, new));
	if (flags & EXP_USEERR)
		return (ex_exp_param_usedef(param, word, new));
}
