/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 19:27:38 by tcase             #+#    #+#             */
/*   Updated: 2019/09/29 14:07:25 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_LINE_H
# define READ_LINE_H
# include <sys/ioctl.h>
# include <term.h>
# include <curses.h>

# define CTRL_D			4
# define CTRL_R			18
# define MSH_BUFF_SIZE	2048
# define MSH_CMD_BUFF 	262144
# define LEFT			4479771
# define RIGHT			4414235
# define UP				4283163
# define DOWN			4348699
# define DELETE			2117294875
# define BSPACE 		127
# define TAB			9
# define PASTE			32975
# define CUT
# define VMODE			10127586
# define UPLINE			18348861490813723
# define DOWNLINE  		18630336467524379
# define WORD_NEXT		73883020516123
# define WORD_BACK		74982532143899
# define LINE_START		71683997260571
# define LINE_END		72783508888347
# define RL_MODE		1
# define HEREDOC_MODE	2

/*
**	status - to handle signal in the middle of reading process.
**	set to 1 on exit of readline
*/
typedef struct			s_rl
{
	int					mode;
	char				*line;
	int					history;
	char				*history_orig;
	t_list				*tab_items;
	size_t				copy_pos;
	size_t				line_len;
	size_t				cur_pos;
}						t_rl;

/*
**  read_line.c
*/
int						read_line(int mode);
void					init_rl(void);

/*
**  rl_input_manipulation.c
*/
void					rl_print_char(long ch);
void					rl_del_char(long ch);

/*
**	rl_move_cur.c
*/
void					rl_move_cur(long ch);

/*
**	rl_big_move.c
*/
void					rl_jump(long ch);

/*
**	rl_vert_move.c
*/
void					rl_vert_move(long ch);

/*
**	rl_copy.c
*/
void					rl_copy(long ch);

/*
**	rl_copy_movement.c
*/
void					rl_copy_movements(void);

/*
**  rl_history.c
**  --rl_calc_hight(char *line);
*/
void					rl_history(long ch);
void					rl_add_history(void);

/*
**  rl_history_replace.c
*/
void					rl_history_change(int position);

/*
**	rl_history_search.c
*/
int						rl_history_search(long ch);

/*
**  rl_tab.c
**  --tl_tab_compare
*/
void					rl_tab(long ch);
void					rl_tab_lastword(char **word, int *word_num);

/*
**	rl_tab_create_list.c
*/
int						rl_tab_create_list(void);

/*
**	rl_newline_check.c
*/
int						rl_newline_check(int mode);

void					rl_start_history(void);
#endif
