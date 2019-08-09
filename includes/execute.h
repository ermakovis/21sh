#ifndef EXECUTE_H
# define EXECUTE_H

typedef struct			s_lch
{
	char				**tokens;
	char				**env;
	int					fd[3];
	char				separator;
}						t_lch;

/*
**  launch_programm.c
**	--lch_create_list.c
*/
void					lch_launch_dups(t_list *list);
void					lch_create_pipes(void);
void					lch_launch_closes(void);
void					launch_program(void);

/*
**	lch_launch.c
**	lch_launch_execute(t_list *list)
**	lch_launch_pop_used(void)
**	lch_launch_pipe_lood(void)
** 	lch_launch_check_executable(char *path)
*/
void					lch_launch(void);

/*
**	lch_redirection.c
*/
void					lch_redirection(int **fd);

/*
**	lch_aggregation.c
*/
void					lch_aggregation_input(char *str, int fd,\
							int **fd_struct);
void					lch_aggregation_output(char *str, int fd,\
							int **fd_struct);

/*
**  lch_checks.c
*/
char					lch_tokens(char ***tokens, int **fd);
void					lch_env(char ***env);
void					lch_check_var(void);
int						lch_check_bins(t_list *list);

/*
**  find_executable.c
*/
void					find_executable(void);


/*
**	lch_list_functions.c
*/
void					add_lch(char **env, char **tokens, char separator,\
							int *fd);
void					del_lch(void *content, size_t size);
void					print_lch(t_list *list);

#endif
