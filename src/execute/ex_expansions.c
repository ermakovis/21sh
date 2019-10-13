#include "msh.h"

void	append_char(char **dest, char ch, size_t buff_size)
{
	size_t	dest_len;

	if (!dest || !*dest)
		return ;
	dest_len = ft_strlen(*dest);
	if (dest_len + 1 >= buff_size * (dest_len / buff_size + 1))
		ft_notrealloc(dest, buff_size * (dest_len / buff_size + 1),\
				buff_size * (dest_len / buff_size + 2));
	(*dest)[dest_len] = ch;
}

void	append_line(char **dest, char *src, size_t buff_size)
{
	size_t	dest_len;
	size_t	src_len;

	if (!dest || !*dest || !src)
		return ;
	dest_len = ft_strlen(*dest);
	src_len = ft_strlen(src);
	if (dest_len + src_len >= buff_size * (dest_len / buff_size + 1))
		ft_notrealloc(dest, buff_size * (dest_len / buff_size + 1),\
				buff_size * (dest_len / buff_size + 2));
	*dest = ft_strcat(*dest, src);
}

void	ex_expansions(t_list **alist)
{
	t_list	*list;

	list = *alist;
	while (list)
	{
		if (((t_token*)list->content)->token_type == WORD)
		{
			ex_expansions_tild(list->content);
			ex_expansions_param(list->content);
			//ex_expansion_command_sub(list);
			//ex_expansion_arithmetic(list);
			ex_expansions_pathname(alist, &list);
			ex_expansions_remquotes(list->content);
		}
		list = list->next;
	}
}
