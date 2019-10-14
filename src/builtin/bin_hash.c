#include "msh.h"

static bool bin_hash_gethits(void)
{
	t_list	*list;
	t_hash	*hash;
	
	list = g_msh->hash;
	while (list)
	{
		hash = list->content;
		if (hash->hits > 0 || hash->searched == 1)
			return (true);
		list = list->next; 
	}
	return (false);
}

static void	bin_hash_clean(void)
{
	t_list	*list;
	t_hash	*hash;

	list = g_msh->hash;
	while (list)
	{
		hash = list->content;
		hash->hits = 0;
		hash->searched = 0;
		list = list->next;
	}
}

void	bin_hash_print(void)
{
	t_list *list;
	t_hash *hash;

	if (!bin_hash_gethits())
	{
		ft_printf("%s: hash: hash table empty\n", g_msh->shell_name);
		return ;
	}
	list = g_msh->hash;
	ft_printf("hits    command\n");
	while (list)
	{
		hash = list->content;
		if (hash->hits > 0 || hash->searched == 1)
			ft_printf("%4d    %s\n", hash->hits, hash->command);
		list = list->next;
	}
}

static int	bin_hash_search(char *command)
{
	t_list	*list;
	t_hash	*hash;

	list = g_msh->hash;
	while (list)
	{
		hash = list->content;
		if (!ft_strcmp(hash->short_name, command))
		{
			hash->searched = 1;
			return (BIN_SUCCESS);
		}
		list = list->next;
	}
	ft_dprintf(2, "%s: hash: %s: not found\n", g_msh->shell_name, command);
	return (BIN_FAILURE);
}

int			bin_hash(t_list *list)
{
	char	**tokens;
	int		i;
	int		ret;

	ret = BIN_SUCCESS;
	ex_tokens(&tokens, list);
	i = 0;
	if (!tokens[i + 1])
	{
		bin_hash_print();
		return (BIN_SUCCESS);
	}
	if (tokens[i + 1] && !ft_strcmp(tokens[i + 1], "-r"))
	{
		bin_hash_clean();
		i++;
	}
	while (tokens[++i])
		if (bin_hash_search(tokens[i]) == BIN_FAILURE)
			ret = BIN_FAILURE;
	return (ret);
}

