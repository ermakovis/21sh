#include "msh.h"

void			lexer(void)
{
	char	*line;
	t_list	*tokens;

	if (!(line = g_msh->rl->line))
		return ;
	while (*line)
	{
		if (lx_operator_check(*line))
			line = line + lx_operator_get(line);
		else if (lx_redirect_check(*line))
			line = line + lx_redirect_get(line);
		else if (lx_word_check(*line))
			line = line + lx_word_get(line);
		else if (*line == '\n')
		{
			line++;
			add_token("<newline>", NEWLINE, NONE);
		}
		else
			line++;
	}
	ft_printf("---LEXER---\n");
	ft_lstiter(g_msh->tokens, &print_token);
	ft_printf("-----------\n\n");
	
}
