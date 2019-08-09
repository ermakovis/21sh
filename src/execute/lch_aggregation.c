#include "msh.h"

void		lch_aggregation_input(char *str, int fd, int **fd_struct)
{
	int		num;

	if (fd > 2)
		return ;
	str += 2;
	num = ft_atoi(str);
	(*fd_struct)[num] = fd;
}

void		lch_aggregation_output(char *str, int fd, int **fd_struct)
{
	if (fd > 2)
		return ;
	str += 2;
	(*fd_struct)[fd] = ft_atoi(str);
}
