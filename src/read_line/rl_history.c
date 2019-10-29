/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 19:53:04 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 21:37:07 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
**	len - 1 to trim <newline> :(
*/

void	rl_add_history(void)
{
	t_list	*new;
	char	*str;
	int		len;

	if (g_msh->rl->mode == HEREDOC_MODE)
		return ;
	str = g_msh->rl->line;
	if ((len = ft_strlen(str)) == 1)
		return ;
	str[len - 1] = 0;
	if (!str || !*str)
		return ;
	if (!(new = ft_lstnew(str, len)))
		cleanup(-1, "Malloc failed at add_token");
	str[len - 1] = '\n';
	ft_lstadd(&(g_msh->history), new);
}

void	rl_history(long ch)
{
	t_rl	*rl;
	int		size;

	if (!(ch == UP || ch == DOWN))
		return ;
	if (!g_msh->history || !g_msh->history->content)
		return ;
	rl = g_msh->rl;
	size = ft_lstsize(g_msh->history) - 1;
	if (ch == UP && rl->history < size)
		rl_history_change(++(rl->history));
	else if (ch == DOWN && rl->history >= 0)
		rl_history_change(--(rl->history));
}

void		rl_store_history_to_g_msh(char *line)
{
	char	**arr;
	int		i;

	i = 0;
	if (!line)
		return ;
	arr = ft_strsplit(line, '\n');
	while (arr[i])
	{
		t_list *new_cur = (t_list *)malloc(sizeof(t_list));
		new_cur->content = (void *)ft_strdup(arr[i]);
		new_cur->content_size = ft_strlen(arr[i]);
		new_cur->next = NULL;
		ft_lstadd_last(&(g_msh->history), new_cur);
		++i;
	}
	i = 0;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void		rl_store_history_to_file(void)
{
	char	*history_path;
	int		fd;
	t_list	*it;

	history_path = get_history_path();
	if (!history_path)
		dprintf(STDERR_FILENO, "42sh: username get error\n");
	fd = open(history_path, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP);
	if (fd < 0)
		dprintf(STDERR_FILENO, "42sh: can't open history's file\n");
	it = g_msh->history;
	while (it)
	{
		write(fd, it->content, ft_strlen(it->content));
		write(fd, "\n", 1);
		it = it->next;
	}
	close(fd);
	free(history_path);
}

void		rl_start_history(void)
{
	int		fd;
	char	*history_path;
	char	line[1024 + 1];
	char	*tmp;
	int		res;

	tmp = NULL;
	history_path = get_history_path();
	if (!history_path)
		dprintf(STDERR_FILENO, "42sh: username get error\n");
	fd = open(history_path, O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP);
	if (fd < 0)
		dprintf(STDERR_FILENO, "42sh: can't open history's file\n");
	while ((res = read(fd, &line, 1024)) > 0)
	{
		line[res] = 0;
		free(tmp);
		tmp = ft_strjoin(tmp, line);
	}
	close(fd);
	rl_store_history_to_g_msh(tmp);
	free(history_path);
}
