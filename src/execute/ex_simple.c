#include "msh.h"

void			ex_simple_exit_check(t_list *list)
{
	t_token		*token;
	char		*word;

	token = list->content;
	word = token->line;
	if (ft_strequ(word, "exit"))
	{
		set_terminal_canon();
		cleanup(0, NULL);
	}
}

int				ex_simple(t_ast *ast)
{
	pid_t		pid;
	int			status;
	
	ex_tokens_assignments(&ast->token);
	if (ast->token == NULL)
		return (SUCCESS);
	ex_simple_exit_check(ast->token);
	if ((pid = fork()) == -1)
		return (FAILURE);
	if (pid == 0)
		exit (ex_command(ast));
	waitpid(pid, &status, 0);
	return (SUCCESS);
}
