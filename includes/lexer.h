#ifndef LEXER_H
# define LEXER_H

typedef struct			s_token
{
	char				*line;
	int					token_type;
	int					operator_type;
}						t_token;

enum					e_tokentype
{
	WORD,
	OPERATOR,
	REDIRECT,
	IO_NUMBER,
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
*/
void					lexer(void);
int						lx_add_token(char *line, int token, int operator);

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
**	lx_struct_functions.c
*/
int						add_token(char *str, int token, int operator);
void					print_token(t_list *list);
void					print_token_line(t_list *list);
void					del_token(void *content, size_t size);
#endif
