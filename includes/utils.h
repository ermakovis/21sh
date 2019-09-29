/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:28:09 by tcase             #+#    #+#             */
/*   Updated: 2019/09/29 14:06:52 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct			s_var
{
	void				*name;
	void				*value;
}						t_var;

typedef struct			s_bin
{
	char				*name;
	void				(*func)(t_list *list);
}						t_bin;
 
typedef struct			s_job
{
	pid_t				pid;
	char				*cmd_line;
}						t_job;

typedef struct			s_cmd
{
	char				*area;
	char				*start;
	char				*clear_line;
	char				*clear_rest;
	char				*cur_start;
	char				*up;
	char				*down;
	char				*left;
	char				*right;
	char				*del;
	char				*highlight_mode_on;
	char				*highlight_mode_off;
	char				*insert_mode_on;
	char				*insert_mode_off;
}						t_cmd;

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
void					msh_exit(t_list *list);
void					msh_env(t_list *list);
void					msh_unsetenv(t_list *list);
void					msh_setenv(t_list *list);
void					msh_echo(t_list *list);

/*
**  msh_cd.c
**  --msh_cd_change
*/
void					msh_cd(t_list *list);

/*
**	msh_jobs.c
*/
void					msh_jobs(t_list *list);

/*
**	msh_fg.c
*/
void					msh_fg(t_list *list);
/*
**  utils.c
*/
void					realloc_check(char **old_ptr, size_t old_size);
void					ft_notrealloc(char **old_ptr, size_t old_size,\
							size_t new_size);
void					display_prompt(void);
void					append_str(char **str, int *i, char *new);
char					*var_to_str(t_var *var);
int						get_char(long *ch);

/*
**	ut_str_functions.c
*/
void					add_str(t_list **list, char *str);
void					printl_str(t_list *list);
void					delete_str(void *content, size_t size);

/*
**  ut_var_functions.c
*/
int						cmp_var(t_var *var, char *data_ref);
void					print_var(t_list *list);
void					set_var(t_list *list, char *var_name, char *var_value);
void					add_var(char *name, char *value, t_list **alist);
void					delete_var(void *content, size_t size);

/*
**	ut_job_functions.c
*/
int						cmp_job(t_job *job, t_job *data_ref);
void					print_job(t_list *list);
void					del_job(void *content, size_t content_size);
t_job					*get_job(pid_t pid, char *cmd_line);
void					add_job(t_list **alist, t_job *job);

/*
**	ut_terminal_mods.c
*/
void					set_terminal_raw(void);
void					set_terminal_canon(void);

/*
**	ut_signals.c
*/
void					ut_signal_sigint(int sig);
void					ut_signal_parent(void);
void					ut_signal_child(void);

/*
**  cleanup.c
*/
void					cleanup(int exit_code, char *message);
void					cl_rl_struct(void);
void					cl_lch_struct(void);
#endif
