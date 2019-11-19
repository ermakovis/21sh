/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 20:45:58 by tcase             #+#    #+#             */
/*   Updated: 2019/11/12 20:46:13 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# define BIN_SUCCESS 0
# define BIN_FAILURE 1
# define BIN_EPICFAILURE 2
# define BIN_FC_LIST (1)
# define BIN_FC_LIST_NONUM (1 << 1)
# define BIN_FC_REV (1 << 2)
# define BIN_FC_NOEDIT (1 << 3)
# define FC_EMPTY "history is empty"
# define FC_USAGE "usage: fc [-e name] [-lnr] [first] [last]"
# define FC_SPEC "history specification out of range"

# define BIN_CD_L (1)
# define BIN_CD_P (1 << 1)

# define BIN_TEST_UN_OPTIONS "bcdefghLnprSstuwxz"
# define BIN_TEST_ERR_BIN "binary operator expected"
# define BIN_TEST_ERR_UN "unary operator expected"
# define BIN_TEST_ERR_TM "too many argumanets"
# define BIN_TEST_ERR_INT "integer expression expected"
# define BIN_TEST_BLOCK (1)
# define BIN_TEST_CHAR (1 << 1)
# define BIN_TEST_DIR (1 << 2)
# define BIN_TEST_EXIST (1 << 3)
# define BIN_TEST_FILE (1 << 4)
# define BIN_TEST_GID (1 << 5)
# define BIN_TEST_SLNK_H (1 << 6)
# define BIN_TEST_SLNK_L (1 << 7)
# define BIN_TEST_STR_NZERO (1 << 8)
# define BIN_TEST_FIFO (1 << 9)
# define BIN_TEST_READ (1 << 10)
# define BIN_TEST_SOCKET (1 << 11)
# define BIN_TEST_SIZE_NZERO (1 << 12)
# define BIN_TEST_FD (1 << 13)
# define BIN_TEST_UID (1 << 14)
# define BIN_TEST_WRITE (1 << 15)
# define BIN_TEST_EXEC (1 << 16)
# define BIN_TEST_STR_ZERO (1 << 17)
# define BIN_TEST_STR_EQU (1 << 18)
# define BIN_TEST_STR_NEQU (1 << 19)
# define BIN_TEST_INT_EQU (1 << 20)
# define BIN_TEST_INT_NEQU (1 << 21)
# define BIN_TEST_INT_GT (1 << 22)
# define BIN_TEST_INT_GE (1 << 23)
# define BIN_TEST_INT_LT (1 << 24)
# define BIN_TEST_INT_LE (1 << 25)

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
int		bin_cd_canon(char **path, int flags);
int		bin_fc(t_list *list);
int		bin_fc_list(char **tokens, t_list **target, int flag);
size_t	bin_fc_list_find_bynum(char *line);
size_t	bin_fc_list_find(char *line);
int		bin_fc_parse(char **tokens, char **editor, int *flag);
int		bin_fc_edit(t_list **list, char *editor);
void	bin_fc_edit_read(char *file_name, char **file_content);
void	bin_fc_edit_create(t_list *list, char **name);
int		bin_test(t_list *list);
int		bin_test_unary(char *arg, int flag);
int		bin_test_binary(char *arg1, char *arg2, int flag);
int		bin_test_get_unary(char *arg, int *flag);
int		bin_test_get_binary(char *arg, int *flag);
int		bin_test_return(int code, char ***tokens);
int		bin_test_error(char *var, char *message, char ***token);

#endif
