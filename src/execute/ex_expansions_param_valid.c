#include "msh.h"

static int	ex_exp_param_valid_printerror(char *message, char *line)
{
	ft_dprintf(2, "%s: %s: %s\n", g_msh->shell_name, line, message);
	return (EXP_FAILURE);
}

static int	ex_exp_param_valid_param(char *param)
{
	int		i;

	i = -1;
	if (!ft_strcmp(param, "?"))
		return (SUCCESS);
	if (ft_isdigit(param[0]))
		return (EXP_FAILURE);
	while (param[++i])
		if (!(ft_isalnum(param[i]) || param[i] == '_'))
			return (EXP_FAILURE);
	return (SUCCESS);
}

static int	ex_exp_param_valid_useerr(char *param, char *word, char *line)
{
	char	*value;

	value = 0;
	if ((value = ex_expansions_param_getline(param)) && *value)
		return (SUCCESS);
	if (word && *word)
		ft_dprintf(2, "%s: %s: %s\n", g_msh->shell_name, param, word);
	else
		ft_dprintf(2, "%s: %s: parameter null or not set\n",\
				g_msh->shell_name, line);
	return (EXP_FAILURE);
}

int			ex_expansions_param_valid(char *param, char *word,\
		int flags, char *line)
{
	if (flags & EXP_ERROR)
		return (ex_exp_param_valid_printerror("bad subtitution", line));
	if (flags & EXP_NUM && flags > EXP_NUM)
		return (ex_exp_param_valid_printerror("bad subtitution", line));
	if (flags & EXP_USEERR)
		return (ex_exp_param_valid_useerr(param, word, line));
	if (ex_exp_param_valid_param(param) == EXP_FAILURE)
		return (ex_exp_param_valid_printerror("incorrect var name", line));
}
