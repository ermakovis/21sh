#include "msh.h"

static int	ex_exp_param_split_simple(char **param, char *line)
{
	int	len;

	len = 0;
	while (line[len] && !ft_strchr("\n\t\'\"\\\t |$;}", line[len]))
		len++;
	if (!(*param = ft_strndup(line, len)))
		cleanup(-1, "Malloc failed at ex_exp_param_split_simple");
	return (len);
}

static int	ex_exp_param_options(char *line, int *flags)
{
	if (!ft_strncmp(line, ":-", 2))
		*flags |= EXP_USEDEF; 
	else if (!ft_strncmp(line, ":=", 2))
		*flags |= EXP_USEASS;
	else if (!ft_strncmp(line, ":?", 2))
		*flags |= EXP_USEERR;
	else if (!ft_strncmp(line, ":+", 2))
		*flags |= EXP_USEALT;
	else if (!ft_strncmp(line, "##", 2))
		*flags |= EXP_REMLARGE; 
	else if (!ft_strncmp(line, "#", 1))
		*flags |= EXP_REMSMALL;
	else if (!ft_strncmp(line, "%%", 2))
		*flags |= EXP_REMLARGE_REV;
	else if (!ft_strncmp(line, "%", 1))
		*flags |= EXP_REMSMALL_REV;
	else
		*flags |= EXP_ERROR;
	if (*flags & EXP_REMSMALL || *flags & EXP_REMSMALL_REV)
		return (1);
	return (2);
}

static int	ex_exp_param_word(char *line, char **word)
{
	int		braces_count;
	int		len;

	len = 0;
	braces_count = 0;
	while (line[len])
	{
		if (line[len] == '{')
			braces_count++;
		if (line[len] == '}' && !braces_count)
			break ;
		if (line[len] == '}')
			braces_count--;
		len++;
	}
	if (!(*word = ft_strndup(line, len)))
		cleanup(-1, "Malloc failed at ex_exp_param_word");
	return (len);
}

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
	while (line[len] && !ft_strchr(":}%#@", line[len]))
		len++;
	if (!(*param = ft_strndup(&line[word_start], len - word_start)))
		cleanup(-1, "Malloc failed at ex_exp_param_split");
	if (line[len] == '}')
		return (len + 1);
	len += ex_exp_param_options(&line[len], flags);
	len += ex_exp_param_word(&line[len], word);
	return (len + 1);
}

//TODO Norminette dat shit
int		ex_expansions_param_replace(char **new, char *line)
{
	char	*param;
	char	*word;
	int		flags;	
	int		len;

	if (!*line)
	{
		append_char(new, '$', NAME_MAX);
		return (0);
	}
	flags = 0;
	param = 0;
	word = 0;
	if ((len = ex_exp_param_split(&param, &word, &flags, line))\
			== EXP_FAILURE)
		return (EXP_FAILURE);
	if (word)	
	{
		ex_expansions_tild(&word);
		if (ex_expansions_param(&word) == EXP_FAILURE)
		{
			ft_memdel((void**)&param);
			ft_memdel((void**)&word);
			return (EXP_FAILURE);
		};
	}
	if (ex_expansions_param_valid(param, word, flags, line) == EXP_FAILURE)
		len = EXP_FAILURE;
	else
		ex_expansions_param_switch(param, word, flags, new);
	ft_memdel((void**)&param);
	ft_memdel((void**)&word);
	return (len);
}
