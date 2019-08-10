#ifndef EXECUTE_H
# define EXECUTE_H

#include <sys/wait.h>

/*
**	execute.c
*/
int			execute(t_ast *ast);
int			ex_semi(t_ast *ast);

/*
**	ex_command.c
*/
int			ex_command(t_ast *ast);
int			ex_builtin(char **tokens);
void		ex_env(char ***env);

/*
**	ex_command_fork.c
*/
int			ex_command_fork(char *cmd, char **tokens, char **env);

/*
**	ex_pipe.c
**	--ex_pipe_edge(t_ast *ast)
**	--ex_pipe_right(t_ast, int fd[2]);
*/
int			ex_pipe(t_ast *ast);
int			ex_pipe_switch(t_ast *left, t_ast *right);

/*
**	ex_tokens.c
**	--ex_tokens_expand(t_token *token)
*/
void		ex_tokens(t_ast *ast, char ***tokens);

/*
**	ex_command_getpath.c
**	--ecg_get_full_path(char *path, char *token, char **new)
**	--ech_exec_join(char *s1, char *s2)
*/
int			ex_getpath(char *token, char **cmd);
int			ex_check_executable(char *path);

#endif
