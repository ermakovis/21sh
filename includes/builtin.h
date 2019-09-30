#ifndef BUILTIN_H
# define BUILTIN_H

int		bin_exit(t_list *list);
int		bin_cd(t_list *list);
int		bin_env(t_list *list);
int		bin_setenv(t_list *list);
int		bin_unsetenv(t_list *list);
int		bin_fg(t_list *list);
int		bin_jobs(t_list *list);

#endif
