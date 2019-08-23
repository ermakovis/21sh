#include "msh.h"

static int		lx_newline(char *line)
{
	add_token("<newline>", 9, NEWLINE, NONE);
	return (1);
}

static void		lx_print(void)
{
	ft_printf("---LEXER---\n");
	ft_lstiter(g_msh->tokens, &print_token);
	ft_printf("-----------\n\n");
}

void			lexer(void)
{
	char	*line;
	t_list	*tokens;

	if (!(line = g_msh->rl->line))
		return ;
	while (*line)
	{
		if (lx_assignment_check(line))
			line += lx_assignment_get(line);
		else if (lx_operator_check(*line))
			line += lx_operator_get(line);
		else if (lx_redirect_check(*line))
			line += lx_redirect_get(line);
		else if (lx_word_check(*line))
			line += lx_word_get(line);
		else if (*line == '\n')
			line += lx_newline(line);
		else
			line++;
	}
	if (g_msh->display_flags & LEXER_V)
		lx_print();
}
