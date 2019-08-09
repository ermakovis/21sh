/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 14:10:41 by tcase             #+#    #+#             */
/*   Updated: 2019/07/31 12:54:27 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H
# include "libft.h"
# include "read_line.h"
# include "lexer.h"
# include "parser.h"
# include "execute.h"
# include <dirent.h>
# include <limits.h>
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct winsize	t_wsize;
typedef struct termios	t_term;
typedef struct stat		t_stat;
typedef struct dirent	t_dir;

typedef struct			s_cmd
{
	char				*area;
	char				*start;
	char				*clear_line;
	char				*clear_rest;
	char				*cur_start;
	char				*up;
	char				*left;
	char				*right;
	char				*del;
	char				*highlight_mode_on;
	char				*highlight_mode_off;
	char				*insert_mode_on;
	char				*insert_mode_off;
}						t_cmd;

typedef struct			s_var
{
	void				*name;
	void				*value;
}						t_var;

typedef struct			s_bin
{
	char				*name;
	void				(*func)(void);
}						t_bin;

typedef struct			s_msh
{
	char				*buffer;
	t_rl				*rl;
	t_cmd				*cmd;
	t_term				*original_state;
	t_ast				*ast;
	t_list				*lch;
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

/*
**  init.c
**  --init_msh(void);
**  --init_cmd(void);
*/
void					init(char **env);

/*
**  init_env.c
*/
void					init_env(char **env);
char					*find_var(t_list *list, char *var_name);

/*
**  init_bins.c
**  --add_bin
*/
int						cmp_bins(t_bin *bin, char *data_ref);
void					init_bins(void);
void					delete_builtins(void *content, size_t size);



/*
**  msh_small_funcs.c
*/
void					msh_env(void);
void					msh_exit(void);
void					msh_unsetenv(void);
void					msh_setenv(void);
void					msh_echo(void);

/*
**  msh_cd.c
**  --msh_cd_change
*/
void					msh_cd(void);

/*
**  utils.c
*/
void					realloc_check(char **old_ptr, size_t old_size);
void					ft_notrealloc(char **old_ptr, size_t old_size,\
							size_t new_size);
void					display_prompt(void);
void					append_str(char **str, int *i, char *new);
char					*var_to_str(t_var *var);

/*
**	ut_str_functions.c
*/
void					printl_str(t_list *list);
void					delete_str(void *content, size_t size);

/*
**  var_functions.c
*/
int						cmp_var(t_var *var, char *data_ref);
void					print_var(t_list *list);
void					set_var(t_list *list, char *var_name, char *var_value);
void					add_var(char *name, char *value, t_list **alist);
void					delete_var(void *content, size_t size);

/*
**  cleanup.c
*/
void					cleanup(int exit_code, char *message);
void					cl_rl_struct(void);
void					cl_lch_struct(void);
#endif
