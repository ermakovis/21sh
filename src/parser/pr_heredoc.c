/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_read_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 20:41:35 by tcase             #+#    #+#             */
/*   Updated: 2019/08/25 13:50:56 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	pr_heredoc_linetolist(t_list **list, char *line, int line_len)
{
	t_list	*new;

	line[line_len] = 0;
	if (!(new = ft_lstnew(line, line_len + 1)))
		cleanup(-1, "Malloc failed at pr_heredoc_linetolist");
	ft_lstadd_last(list, new);
}

static char	*pr_heredoc_listtoline(t_list *list)
{
	char	*line;
	char	*tmp;

	line = NULL;
	while (list)
	{
		tmp = line;
		line = ft_strjoin(line, list->content);
		ft_memdel((void**)&tmp);
		list = list->next;
	}
	return (line);
}

static char	*pr_heredoc_read(t_list *list)
{
	t_list	*ret_list;
	char	*ret;
	char	*line;
	size_t	line_len;

	line = NULL;
	ret_list = NULL;
	cl_rl_struct();
	while (read_line(HEREDOC_MODE))
	{
		line = g_msh->rl->line;
		line_len = ft_strlen(line);
		line[line_len - 1] = 0;
		if (ft_strequ(line, ((t_token*)list->next->content)->line))
			break ;
		line[line_len - 1] = '\n';
		pr_heredoc_linetolist(&ret_list, line, line_len);
		cl_rl_struct();
	}
	ft_lst_sort(&ret_list, &ft_strcmp);
	ret = pr_heredoc_listtoline(ret_list);
	ft_lstdel(&ret_list, &delete_str);
	return (ret);
}

void		pr_heredoc(void)
{
	t_list		*list;
	t_token		*token;

	list = g_msh->tokens;
	while (list)
	{
		token = list->content;
		if (token->token_type == REDIRECT && token->operator_type == DLESS)
			token->heredoc = pr_heredoc_read(list);
		list = list->next;
	}
}
