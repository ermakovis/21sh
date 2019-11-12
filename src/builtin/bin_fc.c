/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_fc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:05:38 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 16:05:40 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	bin_fc_execute(t_list *list)
{
	t_list	*tokens;
	t_ast	*ast;
	char	*tmp;

	while (list)
	{
		ft_printf("> %s\n", list->content);
		tmp = list->content;
		list->content = ft_strjoin(list->content, "\n");
		ft_memdel((void**)&tmp);
		tokens = lexer(list->content);
		ast = parser(&tokens);
		execute(ast);
		ft_lstdel(&tokens, &del_token);
		pr_ast_del(&ast);
		list = list->next;
	}
	return ;
}

void		bin_fc_print(t_list *list, int flags)
{
	while (list)
	{
		if (flags & BIN_FC_LIST_NONUM)
			ft_printf("\t%s\n", list->content);
		else
			ft_printf("%d\t%s\n", list->content_size, list->content);
		list = list->next;
	}
}

static void	bin_fc_switch(t_list **history, char *editor, int flags)
{
	if (flags & BIN_FC_REV)
		ft_lstrev(history);
	if (!(flags & BIN_FC_NOEDIT) && (!(flags & BIN_FC_LIST)))
		bin_fc_edit(history, editor);
	if (flags & BIN_FC_LIST)
		bin_fc_print(*history, flags);
	if (!(flags & BIN_FC_LIST))
		bin_fc_execute(*history);
}

int			bin_fc(t_list *list)
{
	int		flags;
	char	**tokens;
	char	*editor;
	t_list	*history;

	ft_lstpop(&g_msh->history, &delete_str);
	if (!g_msh->history)
		return (bin_print_error(FC_EMPTY, "fc", 0));
	ex_tokens(&tokens, list);
	if (bin_fc_parse(tokens, &editor, &flags) == -1)
		return (bin_print_error(FC_USAGE, "fc", &tokens));
	if (bin_fc_list(tokens, &history, flags) == -1)
		return (bin_print_error(FC_SPEC, "fc", &tokens));
	bin_fc_switch(&history, editor, flags);
	ft_lstdel(&history, &delete_str);
	ft_free_table(&tokens);
	ft_memdel((void**)&editor);
	return (BIN_SUCCESS);
}
