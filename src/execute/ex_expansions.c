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

int		ex_expansions(t_list **alist)
{
	t_list	*list;
	t_token *token;

	list = *alist;
	while (list)
	{
		token = list->content;
		if (token->token_type == WORD)
		{
			ex_expansions_tild(&token->line);
			if (ex_expansions_param(&token->line) == EXP_FAILURE)
				return (EXP_FAILURE);
			//ex_expansion_command_sub(list);
			//ex_expansion_arithmetic(list);
			ex_expansions_pathname(alist, &list);
			ex_expansions_remquotes(list->content);
		}
		list = list->next;
	}
	return (SUCCESS);
}
