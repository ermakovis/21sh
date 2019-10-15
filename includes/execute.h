/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:24:47 by tcase             #+#    #+#             */
/*   Updated: 2019/08/25 11:10:43 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <sys/wait.h>

/*
**	execute.c
*/
int			execute(t_ast *ast);
int			ex_semi(t_ast *ast);

/*
**	ex_common.c
*/
void		ex_tokens(char ***tokens, t_list *list);
void		ex_env(char ***env);
void		ex_command_setpgid(bool bg);
int			ex_builtin(t_list *list);
int			ex_exit_status(int status);
int			ex_set_return_var(int ret);

/*
**	ex_simple.c
*/
int			ex_simple(t_ast *ast);

/*
**	ex_job.c
*/
int			ex_wait(t_job *job);
int			ex_job(pid_t pid, t_ast *ast);
void		ex_job_check(int sig);

/*
**	ex_assignments.c
*/
void		ex_assignments(t_list **list);

/*
**	ex_redirections.c
*/
int		ex_redirections(t_list *list);
int		ex_redirections_check(char *path);

/*
**	ex_redirections_simple.c
*/
int		ex_redirections_simple(t_list *list);

/*
**	ex_redirections_agreg.c
*/
int		ex_redirections_agreg(t_list *list);

/*
**	ex_redirections_heredoc.c
*/
void	ex_redirections_heredoc(t_list *list);

/*
**	ex_globbing.c
*/
bool		ex_globbing(char *str, char *pat, char *b_str, char *b_pat);
/*
**	ex_pipe.c
**	--ex_pipe_edge(t_ast *ast)
**	--ex_pipe_right(t_ast, int fd[2]);
*/
int			ex_pipe(t_ast *ast);
int			ex_pipe_switch(t_ast *left, t_ast *right);

void		ex_expansions(t_list **list);
void		append_line(char **dest, char *src, size_t buff_size);
void		append_char(char **dest, char ch, size_t buff_size);
void		ex_expansions_tild(t_token *token);
void		ex_expansions_param(t_token *token);
void		ex_expansions_remquotes(t_token *token);
void		ex_expansions_pathname(t_list **alist, t_list **list);

int			ex_getpath(char *token, char **cmd);
int			ex_check_executable(char *path);

#endif
