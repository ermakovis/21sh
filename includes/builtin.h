#ifndef BUILTIN_H
# define BUILTIN_H
# define BIN_SUCCESS 0
# define BIN_FAILURE 1
# define BIN_EPICFAILURE 2
# define BIN_FC_LIST (1)
# define BIN_FC_LIST_NONUM (1 << 1)
# define BIN_FC_REV (1 << 2)
# define BIN_FC_NOEDIT (1 << 3)


int		bin_print_error(char *message, char *function_name, char ***tokens);
int		bin_set(t_list *list);
int		bin_unset(t_list *list);
int		bin_export(t_list *list);
int		bin_exit(t_list *list);
int		bin_env(t_list *list);
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
int		bin_history(t_list *list);
int		bin_cd(t_list *list);
int		bin_cd_cdpath(char **path);
int		bin_fc(t_list *list);
int		bin_fc_list(char **tokens, t_list **target, int flag);
int		bin_fc_parse(char **tokens, char **editor, int *flag);
int		bin_fc_edit(t_list **list, char *editor);

#endif
