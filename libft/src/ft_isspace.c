#include "libft.h"

int		ft_isspace(int ch)
{
	if (ch == ' ' || ch == '\t')
		return (1);
	return (0);
}
