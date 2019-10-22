#ifndef BUILTIN_H
# define BUILTIN_H
# define BIN_SUCCESS 0
# define BIN_FAILURE 1
# define BIN_EPICFAILURE 2

int		bin_exit(t_list *list);
int		bin_cd(t_list *list);
int		bin_env(t_list *list);
int		bin_setenv(t_list *list);
int		bin_unsetenv(t_list *list);
int		bin_fg(t_list *list);
int		bin_bg(t_list *list);
int		bin_jobs(t_list *list);
int		bin_alias(t_list *list);
int		bin_alias_action(char *line);
int		bin_unalias(t_list *list);
int		bin_echo(t_list *list);
int		bin_hash(t_list *list);
int		bin_type(t_list *list);
int		bin_true(t_list *list);
int		bin_false(t_list *list);

#endif
