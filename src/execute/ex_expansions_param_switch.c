#include "msh.h"

static void ex_expansions_param_number(char *param, char **new)
{
	char	*itoa_line;
	int		len;
	
	len = ft_strlen(ex_expansions_param_getline(param));
	if (!(itoa_line = ft_itoa(len)))
		cleanup(-1, "Malloc failed at ex_expansions_param_number");
	append_line(new, itoa_line, NAME_MAX); 
	ft_memdel((void**)&itoa_line);
}

void ex_expansions_param_simple(char *param, char **new)
{
	char	*line;

	line = 0;
	if ((line = ex_expansions_param_getline(param)))
		append_line(new, line, NAME_MAX);
}

void		ex_expansions_param_switch(char *param, char *word,\
			int flags, char **new)
{
	if (flags & EXP_NUM)
		ex_expansions_param_number(param, new);
	if (flags & EXP_REMSMALL || flags & EXP_REMLARGE || flags & EXP_REMSMALL_REV\
		|| flags & EXP_REMLARGE_REV)
		ex_expansions_param_rem(param, word, flags, new);
	if (flags & EXP_USEDEF || flags & EXP_USEASS\
		|| flags & EXP_USEALT || flags & EXP_USEERR)
		ex_expansions_param_use(param, word, flags, new);
	else if (flags == 0)
		ex_expansions_param_simple(param, new);

}
