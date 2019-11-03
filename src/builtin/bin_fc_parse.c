#include "msh.h"

static int		add_flag(char *str, int *flags)
{
	int		shift;
	int		i;
	char	line[] = "lnrs";

	shift = 0;
	i = 0;
	while (str[++i])
	{
		if ((shift = ft_strchrlen(line, str[i])) == -1)
			return (0);
		*flags |= (1 << shift);
	}
	return (1);
}

static int		bin_fc_editor(char **options, char **editor, int *count)
{
	int		i;

	*count = 1;
	if (!options[*count])
	{
		if (ex_getpath("vim", editor) == FAILURE)
			return (BIN_FAILURE);
		return (BIN_SUCCESS);
	}
	if (!ft_strcmp(options[*count], "-e") && !options[*count + 1])
		return (BIN_FAILURE);
	if (!ft_strcmp(options[*count], "-e") && options[*count + 1])
	{
		if (ex_getpath(options[*count + 1], editor) == FAILURE)
			return(BIN_FAILURE);
		*count += 2;
		return (BIN_SUCCESS);
	}
	if (ex_getpath("vim", editor) == FAILURE)
			return (BIN_FAILURE);
	return (BIN_SUCCESS);
}

int				bin_fc_parse(char **options, char **editor, int *flags)
{
	int		count;

	count = 0;
	*flags = 0;
	if (bin_fc_editor(options, editor, &count) == BIN_FAILURE)
		return (-1);
	while (options[count] && options[count][0] == '-' && options[count][1])
	{
		if (!(add_flag(options[count], flags)))
			return (-1);
		count++;
	}
	return (count);
}
