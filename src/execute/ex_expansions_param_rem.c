#include "msh.h"

static void ex_exp_param_remlarge_rev(char *param, char *word, char **new)
{
	char	*line;
	int		i;
	int		pos;

	if (!(line = ex_expansions_param_getline(param)))
		return ;
	if (!(line = ft_strdup(line)))
		cleanup(-1, "Malloc failed at param_simple");
	pos = -1;
	i = ft_strlen(line) - 1;
	while (i > -1)
	{
		if (ex_globbing(&line[i], word, 0, 0))
			pos = i;
		i--;
	}
	if (pos > -1)
		line[pos] = 0;
	append_line(new, line, NAME_MAX);
	ft_memdel((void**)&line);
}

static void ex_exp_param_remsmall_rev(char *param, char *word, char **new)
{
	char	*line;
	int		i;

	if (!(line = ex_expansions_param_getline(param)))
		return ;
	if (!(line = ft_strdup(line)))
		cleanup(-1, "Malloc failed at param_simple");
	i = ft_strlen(line) - 1;
	while (i > -1)
	{
		if (ex_globbing(&line[i], word, 0, 0))
		{
			line[i] = 0;
			break ;
		}
		i--;
	}
	append_line(new, line, NAME_MAX);
	ft_memdel((void**)&line);
}

static void ex_exp_param_remlarge(char *param, char *word, char **new)
{
	char	*line;
	char	save;
	int		i;
	int		pos;

	i = 0;
	pos = -1;
	if (!(line = ex_expansions_param_getline(param)))
		return ;
	if (!(line = ft_strdup(line)))
		cleanup(-1, "Malloc failed at param_simple");
	while (line[i])
	{
		save = line[i + 1];
		line[i + 1] = 0;
		if (ex_globbing(line, word, 0, 0))
			pos = i;
		line[i + 1] = save;
		i++;
	}
	if (pos > -1)
		ft_memmove(line, &line[pos + 1], ft_strlen(&line[pos]) + 1);
	append_line(new, line, NAME_MAX);
	ft_memdel((void**)&line);
}

static void ex_exp_param_remsmall(char *param, char *word, char **new)
{
	char	*line;
	char	save;
	int		i;

	i = 0;
	if (!(line = ex_expansions_param_getline(param)))
		return ;
	if (!(line = ft_strdup(line)))
		cleanup(-1, "Malloc failed at param_simple");
	while (line[i])
	{
		save = line[i + 1];
		line[i + 1] = 0;
		if (ex_globbing(line, word, 0, 0))
		{
			line[i + 1] = save;
			ft_memmove(line, &line[i + 1], ft_strlen(&line[i]) + 1);
			break ;
		}
		line[i + 1] = save;
		i++;
	}
	append_line(new, line, NAME_MAX);
	ft_memdel((void**)&line);
}

void	ex_expansions_param_rem(char *param, char *word, int flags, char **new)
{
	if (!param || !*param)
		return ;
	if (!word || !*word)
		return (ex_expansions_param_simple(param, new));
	if (flags & EXP_REMSMALL)
		return (ex_exp_param_remsmall(param, word, new));
	if (flags & EXP_REMLARGE)
		return (ex_exp_param_remlarge(param, word, new));
	if (flags & EXP_REMSMALL_REV)
		return (ex_exp_param_remsmall_rev(param, word, new));
	if (flags & EXP_REMLARGE_REV)
		return (ex_exp_param_remlarge_rev(param, word, new));
}


