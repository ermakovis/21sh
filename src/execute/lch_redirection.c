#include "msh.h"

void		lch_redirection_append(char *str, int fd, int **fd_struct)
{	
	int		fd_file;

	if (fd > 2)
		return ;
	str += 2;
	if ((fd_file = open(str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU)) == -1)
		return ;
	(*fd_struct)[fd] = fd_file;
}

void		lch_redirection_trunc(char *str, int fd, int **fd_struct)
{	
	int		fd_file;

	if (fd > 2)
		return ;
	str++;
	if ((fd_file = open(str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) == -1)
		return ;
	(*fd_struct)[fd] = fd_file;
}

void		lch_redirection_input(char *str, int fd, int **fd_struct)
{	
	int		fd_file;

	if (fd > 2)
		return ;
	str++;
	if ((fd_file = open(str, O_RDONLY)) == -1)
		return ;
	(*fd_struct)[fd] = fd_file;
}

void		lch_redirection_heredoc(char *str, int fd)
{	
	return ;
}
/*
**	don't touch order!
*/
void		lch_redirection(int **fd_struct)
{
	char	*str;
	int		num;


	str = g_msh->tok->content;
	num = ft_atoi(str);
	str += ft_nbrlen(num, 10);
	if (ft_strnequ(str, ">&", 2))
		lch_aggregation_input(str, num, fd_struct);
	else if (ft_strnequ(str, "<&", 2))
		lch_aggregation_output(str, num, fd_struct);
	else if (ft_strnequ(str, ">>", 2))
		lch_redirection_append(str, num, fd_struct);
	else if (str[0] == '>')
		lch_redirection_trunc(str, num, fd_struct);
	else if (ft_strnequ(str, "<<", 2))
		lch_redirection_heredoc(str, num);
	else if (str[0] == '<')
		lch_redirection_input(str, num, fd_struct);
}
