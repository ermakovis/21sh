/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:27:04 by tcase             #+#    #+#             */
/*   Updated: 2019/09/29 13:49:13 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct			s_token
{
	char				*line;
	int					token_type;
	int					operator_type;
	char				*heredoc;
	char				*full_command;
}						t_token;

enum					e_tokentype
{
	WORD,
	OPERATOR,
	REDIRECT,
	ASSIGNMENT,
	NEWLINE
};

enum					e_operators
{
	NONE,
	SEMI,
	AND_IF,
	AND,
	OR_IF,
	PIPE,
	DLESS,
	LESS_AND,
	LESS,
	DMORE,
	MORE_AND,
	MORE
};
/*
**	lexer.c
**	--lx_newline(char *line)
**	--lx_print(void)
*/
t_list					*lexer(char *line);
char					*lx_line(char *line, int len);
t_list					*lx_tokens(char *line);

/*
**	lx_operator.c
*/
int						lx_operator_check(char ch);
int						lx_operator_get(char *line, t_list **tokens);

/*
**	lx_redirect.c
*/
int						lx_redirect_check(char ch);
int						lx_redirect_get(char *line, t_list **tokens);

/*
**	lx_word_check.c
**	--lx_word_dqoute_len(char *line, int len)
**	--lx_word_add_token(char *line)
*/
int						lx_word_check(char ch);
int						lx_word_get(char *line, t_list **tokens);

/*
**	lx_assignment.c
*/
int						lx_assignment_check(char *line);
int						lx_assignment_get(char *line, t_list **tokens);

/*
**	lx_alias.c
*/
void					lx_alias(t_list **alist);

/*
**	lx_struct_functions.c
*/
int						cmp_token(t_token *token_a, t_token *token_b);
int						add_token(t_list **alist, char *line, int tok, int op);
void					print_token(t_list *list);
void					print_token_line(t_list *list);
void					del_token(void *content, size_t size);
#endif
