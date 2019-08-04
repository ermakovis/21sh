#include "msh.h"

void	add_lch(char **env, char **tokens, char separator)
{
	t_list	*list;
	t_lch	*lch;
	size_t	size;
	
	size = sizeof(t_lch);
	if (!(lch = (t_lch*)malloc(size)))
		cleanup(-1, "Malloc failed at add_lch 1");
	ft_bzero(lch, size);	
	lch->fd[0] = -1;
	lch->fd[1] = -1;
	lch->fd[2] = -1;
	lch->tokens = tokens;	
	lch->env = env;
	lch->separator = separator;
	if (!(list = ft_lstnew(lch, size)))
		cleanup(-1, "Malloc failed at add_lch 2");
	ft_lstadd_last(&g_msh->lch, list); 
}

void	del_lch(void *content, size_t size)
{
	t_lch *lch;

	(void)size;
	lch = content;
	ft_free_table(&lch->env);
	ft_free_table(&lch->tokens);
	lch->fd[0] = -1;
	lch->fd[1] = -1;
	lch->fd[2] = -1;
	lch->separator = 0;
}

void	print_lch(t_list *list)
{
	int		i;
	t_lch	*lch;

	i = -1;
	lch = list->content;
	while ((lch->tokens)[++i])
		ft_printf("%s ", lch->tokens[i]);
	ft_printf("\n%d %d %d %c\n", lch->fd[0], lch->fd[1],\
		lch->fd[2], lch->separator);
}

