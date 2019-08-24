/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:27:04 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 20:36:31 by tcase            ###   ########.fr       */
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
void					lexer(void);

/*
**	lx_operator.c
*/
int						lx_operator_check(char ch);
int						lx_operator_get(char *line);

/*
**	lx_redirect.c
*/
int						lx_redirect_check(char ch);
int						lx_redirect_get(char *line);

/*
**	lx_word_check.c
**	--lx_word_dqoute_len(char *line, int len)
**	--lx_word_add_token(char *line)
*/
int						lx_word_check(char ch);
int						lx_word_get(char *line);

/*
**	lx_assignment.c
*/
int						lx_assignment_check(char *line);
int						lx_assignment_get(char *line);

/*
**	lx_struct_functions.c
*/
int						add_token(char *str, int line_len,\
							int token, int operator);
void					print_token(t_list *list);
void					print_token_line(t_list *list);
void					del_token(void *content, size_t size);
#endif
