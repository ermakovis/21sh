#include "msh.h"

void	init_alias(void)
{
	int		fd;
	char	*line;

	if ((fd = open("./.42sh_alias", O_RDONLY)) == -1)
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strnequ(line, "alias ", 6)) 
			bin_alias_action(line + 6);
		ft_strdel(&line);
	}
	close(fd);
}
