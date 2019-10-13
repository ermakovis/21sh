#include "msh.h"

static int	bin_echo_isspecial(char ch)
{
	return (ch == 'a' || ch == 'b' || ch == 'c' || ch == 'f' || ch == 'n'\
	 	|| ch == 't' || ch == 'v' || ch == '0');
}

static int	bin_echo_printspecial(char ch)
{
	if (ch == 'a')
		ft_printf("\a");
	else if (ch == 'b')
		ft_printf("\b");
	else if (ch == 'c')
		return (BIN_FAILURE);
	else if (ch == 'f')
		ft_printf("\f");
	else if (ch == 'n')
		ft_printf("\n");
	else if (ch == 't')
		ft_printf("\t");
	else if (ch == 'v')
		ft_printf("\v");
//	else if (ch == '0')
//		ft_printf("\033");
	return (BIN_SUCCESS);
}

static int	bin_echo_printline(char *line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\\')
		{
			i++;
			if (bin_echo_isspecial(line[i]))
			{
				if (bin_echo_printspecial(line[i]) == BIN_FAILURE)
					return (BIN_FAILURE);
			}
			else
				ft_printf("%c", line[i]);
		}
		else
			ft_printf("%c", line[i]);
	}
	return (BIN_SUCCESS);
}

int			bin_echo(t_list *list)
{
	char	**tokens;
	int		nl_flag;
	int		i;
	int		ret;

	i = 0;
	nl_flag = 0;
	ret = BIN_SUCCESS;
	ex_tokens(&tokens, list);
	if (tokens[i + 1] && (nl_flag = ft_strequ(tokens[i + 1], "-n")))
		i++;
	while (tokens[++i])
	{
		if ((ret = bin_echo_printline(tokens[i])) == BIN_FAILURE)
			break ;
		if (tokens[i + 1])
			ft_printf(" ");
	}
	if (!nl_flag)
		ft_printf("\n");
	ft_free_table(&tokens);
	return (ret);
}
