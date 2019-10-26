/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 19:59:12 by tcase             #+#    #+#             */
/*   Updated: 2019/09/29 15:30:27 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int				get_char(long *ch)
{
	*ch = 0;
	read(STDIN_FILENO, ch, sizeof(long));
	return (1);
}

void		realloc_check(char **old_ptr, size_t old_size)
{
	size_t	new_size;

	if (!old_ptr || !*old_ptr || !**old_ptr || old_size % MSH_BUFF_SIZE != 0)
		return ;
	new_size = ((old_size / MSH_BUFF_SIZE) + 1) * MSH_BUFF_SIZE;
	ft_notrealloc(old_ptr, old_size, new_size);
}

void		ft_notrealloc(char **old_ptr, size_t old_size, size_t new_size)
{
	char	*new_ptr;

	if (!old_ptr || !*old_ptr)
		return ;
	if (!(new_ptr = ft_strnew(new_size)))
		cleanup(-1, "Failed to realloc");
	ft_memcpy(new_ptr, *old_ptr, old_size);
	ft_memdel((void**)old_ptr);
	*old_ptr = new_ptr;
}

char		*var_to_str(char *name, char *value)
{
	char	*ret;
	size_t	name_len;
	size_t	val_len;

	name_len = ft_strlen(name);
	val_len = ft_strlen(value);
	if (!(ret = (char*)ft_memalloc(name_len + val_len + 2)))
		cleanup(-1, "Malloc failed at var_to_srt");
	ft_memcpy(ret, name, name_len);
	ret[name_len] = '=';
	ft_memcpy(ret + name_len + 1, value, val_len);
	return (ret);
}

void		append_str(char **str, int *i, char *new)
{
	int		j;

	if (!new || !*new || !i || !new)
		return ;
	j = -1;
	while (new[++j])
	{
		realloc_check(str, *i + 1);
		(*str)[(*i)++] = new[j];
	}
}

void		display_prompt(void)
{
	char	*home;
	char	*pwd;
	int		home_len;

	if (!isatty(0))
		return ;
	home = find_var(g_msh->env, "HOME");
	pwd = find_var(g_msh->env, "PWD");
	home_len = ft_strlen(home);
	if (ft_strnequ(pwd, home, home_len))
	{
		ft_printf("~%s $: ", pwd + home_len);
	}
	else
		ft_printf("%s $: ", pwd);
}
