#include "msh.h"

static int	ex_exp_param_split_simple(char **param, char *line)
{
	int	len;

	len = 0;
	while (line[len] && !ft_strchr("\n\t\'\"\\\t |$;", line[len]))
		len++;
	if (!(*param = ft_strndup(line, len)))
		cleanup(-1, "Malloc failed at ex_exp_param_split_simple");
	return (len);
}

static int	ex_exp_param_options(char *line, int *flags)
{
	if (ft_strncmp(line, ":-", 2))
		*flags |= EXP_USEDEF; 
	else if (ft_strncmp(line, ":=", 2))
		*flags |= EXP_USEASS;
	else if (ft_strncmp(line, ":?", 2))
		*flags |= EXP_USEERR;
	else if (ft_strncmp(line, ":+", 2))
		*flags |= EXP_USEALT;
	else if (ft_strncmp(line, "##", 2))
		*flags |= EXP_REMLARGE; 
	else if (ft_strncmp(line, "#", 1))
		*flags |= EXP_REMSMALL;
	else if (ft_strncmp(line, "%%", 2))
		*flags |= EXP_REMLARGE_REV;
	else if (ft_strncmp(line, "%", 1))
		*flags |= EXP_REMSMALL_REV;
	else
		*flags |= EXP_ERROR;
	if (*flags & EXP_REMSMALL || *flags & EXP_REMSMALL_REV)
		return (1);
	return (2);
}

//TODO: Correct word len in case of nested param
static int	ex_exp_param_split(char **param, char **word,\
	int *flags, char *line)
{
	int		len;
	int		word_start;

	len = 0;
	if (line[len] != '{')
		return (ex_exp_param_split_simple(param, line));
	len++;
	if (line[len] == '#' && len++)
		*flags |= EXP_NUM;
	word_start = len;
	while (line[len] && !ft_strchr(":}#@", line[len]))
		len++;
	if (!(*param = ft_strndup(&line[word_start], len - word_start)))
		cleanup(-1, "Malloc failed at ex_exp_param_split");
	if (line[len] == '}')
		return (len + 1);
	len += ex_exp_param_options(&line[len], flags);
	word_start = len;
	while(line[len] && line[len] != '}')
		len++;
	if (!(*word = ft_strndup(&line[word_start], len - word_start)))
		cleanup(-1, "Malloc failed at ex_exp_param_split");
	return (len + 1);
}

int		ex_expansions_param_replace(char **new, char *line)
{
	char	*parameter;
	char	*word;
	int		flags;	
	int		len;

	if (!*line)
	{
		append_char(new, '$', NAME_MAX);
		return (0);
	}
	parameter = 0;
	word = 0;
	flags = 0;
	if ((len = ex_exp_param_split(&parameter, &word, &flags, line))\
		== EXP_FAILURE)
		return (EXP_FAILURE);
	ft_printf("%s - %s - %b\n", parameter, word, flags);
	ex_expansions_param_switch(parameter, word, flags, new);
	return (len);

}
