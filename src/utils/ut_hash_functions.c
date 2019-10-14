#include "msh.h"

int		cmp_hash(t_hash *hash, char *data_ref)
{
	return (ft_strcmp(hash->short_name, data_ref));
}

void	del_hash(void *content, size_t size)
{
	t_hash	*hash;

	(void)size;
	hash = content;
	ft_memdel((void**)&hash->command);
	ft_memdel((void**)&hash->short_name);
	ft_memdel((void**)&content);
}

void	print_hash(t_list *list)
{
	t_hash	*hash;

	hash = list->content;
	ft_printf("%d\t%s\t%s\n", hash->hits, hash->short_name, hash->command);
}

void	add_hash(char *command, char *short_name)
{
	t_list	*list;
	t_hash	*hash;
	size_t	size;

	size = sizeof(t_hash);
	if (!(hash = (t_hash*)ft_memalloc(size)))
		cleanup(-1, "Malloc failed at add_hash");
	hash->command = command;
	hash->short_name = short_name;
	if (!(list = ft_lstnew(hash, size)))
		cleanup(-1, "Malloc failed at add_hash");
	ft_memdel((void**)&hash);
	ft_lstadd(&g_msh->hash, list);
}
