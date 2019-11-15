/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:53:13 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 15:53:22 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int		bin_print_error(char *message, char *function_name, char ***tokens)
{
	if (message)
		ft_dprintf(2, "%s: %s: %s\n",\
			g_msh->shell_name, function_name, message);
	if (tokens && *tokens)
		ft_free_table(tokens);
	return (BIN_FAILURE);
}
