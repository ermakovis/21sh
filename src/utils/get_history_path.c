
#include "msh.h"

char				*get_history_path(void)
{
	struct passwd	*pass;
	char			*ret;
	char			*tmp;

	ret = NULL;
	pass = getpwuid(getuid());
	if (!pass) {
		return (ret);
	}
	ret = ft_strjoin("/Users/", pass->pw_name);
	tmp = ret;
	ret = ft_strjoin(ret, "/");
	free(tmp);
	tmp = ret;
	ret = ft_strjoin(ret, ".42sh_history");
	free(tmp);
	return (ret);
}