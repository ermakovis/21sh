#include "msh.h"

static int		rl_quotes_check(char *line)
{
	int		i;
	int		dquote;
	int		squote;

	i = -1;
	dquote = 0;
	squote = 0;
	while (line[++i])
	{
		if (line[i] == '\\' && squote == 0)
			i++;
		else if (line[i] == '\'' && dquote == 0)
			squote ^= 1;
		else if (line[i] == '\"' && squote == 0)
			dquote ^= 1;
	}
	if (dquote || squote)
	{
		rl_print_char('\n');
		ft_printf("> ");
	}
	return (!(dquote || squote));
}

static int		rl_bslash_check(char *line)
{
	int		i;
	int		is_quoted;

	i = -1;
	while (line[++i])
	{
		is_quoted = 0;
		if (line[i] == '\\')
		{
			is_quoted = 1;
			i++;
		}
		if (!line[i] && is_quoted)
		{
			rl_print_char('\n');
			ft_printf("> ");
			return (0);
		}
	}
	return (1);
}

int		rl_braces_check(char *line)
{
	char	pile[1000];
	int		pile_size;
	bool	mismatch;

	pile_size = 0;
	mismatch = false;
	while (*line && mismatch == false)
	{
		if (*line == '(')
			pile[pile_size++] = ')';
		else if (*line == '[')
			pile[pile_size++] = ']';
		else if (*line == '{')
			pile[pile_size++] = '}';
		else if (*line == ')' || *line == ']' || *line == '}')
			if (pile_size == 0 || pile[--pile_size] != *line)
				mismatch = true;
		line++;	
	}
	if (mismatch == true && ft_dprintf(2, "\n%s: braces are unbalanced\n",\
		g_msh->shell_name))
		return (2);
	if (pile_size > 0 && ft_printf("\n> "))
		return (1);
	return (0);
}

int		rl_newline_check(void)
{
	char *line;

	line = g_msh->rl->line;
	if (rl_quotes_check(line) == 0)
		return (1);
	if (rl_bslash_check(line) == 0)
		return (1);
	return (rl_braces_check(line));

}
