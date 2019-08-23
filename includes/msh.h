/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 14:10:41 by tcase             #+#    #+#             */
/*   Updated: 2019/08/10 19:49:49 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H
# include "libft.h"
# include "read_line.h"
# include "lexer.h"
# include "parser.h"
# include "execute.h"
# include "utils.h"
# include <dirent.h>
# include <limits.h>
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>

# define FLAGS "lp"
# define LEXER_V (1 << 0)
# define PARSER_V (1 << 1)

# define SUCCESS 1
# define FAILURE 0

typedef struct winsize	t_wsize;
typedef struct termios	t_term;
typedef struct stat		t_stat;
typedef struct dirent	t_dir;

typedef struct			s_msh
{
	int					display_flags;
	char				*shell_name;
	char				*copy_buffer;
	t_rl				*rl;
	t_cmd				*cmd;
	t_term				*original_state;
	t_ast				*ast;
	t_list				*tokens;
	t_list				*var;
	t_list				*env;
	t_list				*bin;
	t_list				*history;
}						t_msh;

t_msh					*g_msh;

/*
**  main.c
*/
void					set_terminal_canon(void);
void					set_terminal_raw(void);

#endif
