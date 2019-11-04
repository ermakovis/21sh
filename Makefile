# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcase <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/06 11:31:10 by tcase             #+#    #+#              #
#    Updated: 2019/09/28 21:42:49 by tcase            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=msh

CC=gcc
FLAGS=-g# -Wall -Werror -Wextra

SRC_DIR=./src
RL_DIR=./src/read_line
LX_DIR=./src/lexer
PR_DIR=./src/parser
EXE_DIR=./src/execute
BIN_DIR=./src/builtin
UT_DIR=./src/utils
LIB_DIR=./libft
OBJ_DIR=./obj

SRC_NAME=main.c
RL_NAME=read_line.c\
	rl_input_manipulation.c\
	rl_move_cur.c\
	rl_vert_move.c\
	rl_jump.c\
	rl_copy.c\
	rl_copy_movement.c\
	rl_history.c\
	rl_history_change.c\
	rl_history_search.c\
	rl_tab.c\
	rl_tab_create_list.c\
	rl_newline_check.c\
	rl_search_history.c
LX_NAME=lexer.c\
	lx_operator.c\
	lx_redirect.c\
	lx_word.c\
	lx_assignment.c\
	lx_alias.c\
	lx_history.c\
	lx_history_find.c\
	lx_struct_functions.c
PR_NAME=parser.c\
	pr_heredoc.c\
	pr_syntax_check.c\
	pr_ast_create.c\
	pr_ast_functions.c\
	pr_ast_fillcommand.c
BIN_NAME=bin_exit.c\
	bin_export.c\
	bin_set.c\
	bin_unset.c\
	bin_cd.c\
	bin_fg.c\
	bin_bg.c\
	bin_jobs.c\
	bin_env.c\
	bin_alias.c\
	bin_unalias.c\
	bin_echo.c\
	bin_type.c\
	bin_hash.c\
	bin_true_false.c\
	bin_history.c\
	bin_fc.c\
	bin_fc_list.c\
	bin_fc_parse.c\
	bin_fc_edit.c\
	bin_functions.c
EXE_NAME=execute.c\
	ex_simple.c\
	ex_job.c\
	ex_job_state.c\
	ex_job_functions.c\
	ex_pipe.c\
	ex_common.c\
	ex_tokens.c\
	ex_getpath.c\
	ex_assignments.c\
	ex_redirections.c\
	ex_redirections_simple.c\
	ex_redirections_agreg.c\
	ex_redirections_heredoc.c\
	ex_globbing.c\
	ex_expansions.c\
	ex_expansions_tild.c\
	ex_expansions_param.c\
	ex_expansions_param_valid.c\
	ex_expansions_param_replace.c\
	ex_expansions_param_switch.c\
	ex_expansions_param_rem.c\
	ex_expansions_param_use.c\
	ex_expansions_remquotes.c\
	ex_expansions_pathname.c
UT_NAME=init.c\
	init_env.c\
	init_bins.c\
	init_alias.c\
	init_hash.c\
	init_history.c\
	utils.c\
	ut_checks.c\
	ut_str_functions.c\
	ut_var_functions.c\
	ut_job_functions.c\
	ut_hash_functions.c\
	ut_terminal_mods.c\
	ut_signals.c\
	cleanup.c\
	get_history_path.c

RL = $(addprefix $(OBJ_DIR)/, $(RL_NAME:.c=.o))
LX = $(addprefix $(OBJ_DIR)/, $(LX_NAME:.c=.o))
PR = $(addprefix $(OBJ_DIR)/, $(PR_NAME:.c=.o))
EXE = $(addprefix $(OBJ_DIR)/, $(EXE_NAME:.c=.o))
BIN = $(addprefix $(OBJ_DIR)/, $(BIN_NAME:.c=.o))
UT = $(addprefix $(OBJ_DIR)/, $(UT_NAME:.c=.o))
SRC = $(addprefix $(OBJ_DIR)/, $(SRC_NAME:.c=.o))
OBJ = $(SRC) $(RL) $(LX) $(PR) $(BIN) $(EXE) $(UT) 
INC = -I ./includes -I $(LIB_DIR)/includes

all: $(NAME)

$(NAME) : $(OBJ)
	@make -s -C $(LIB_DIR)
	@$(CC) -o $(NAME) $(SRC) $(RL) $(LX) $(PR) $(EXE) $(UT) $(BIN)\
		$(LIB_DIR)/libft.a $(INC) -lcurses $(FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p obj
	@$(CC) -o $@ -c $< $(INC) $(FLAGS)
	@echo "\033[0m\033[36m$(notdir $<)\033[1m\033[34m OK\033[0m"

$(OBJ_DIR)/%.o: $(RL_DIR)/%.c
	@$(CC) -o $@ -c $< $(INC) $(FLAGS)
	@echo "\033[0m\033[36m$(notdir $<)\033[1m\033[34m OK\033[0m"

$(OBJ_DIR)/%.o: $(LX_DIR)/%.c
	@$(CC) -o $@ -c $< $(INC) $(FLAGS)
	@echo "\033[0m\033[36m$(notdir $<)\033[1m\033[34m OK\033[0m"

$(OBJ_DIR)/%.o: $(PR_DIR)/%.c
	@$(CC) -o $@ -c $< $(INC) $(FLAGS)
	@echo "\033[0m\033[36m$(notdir $<)\033[1m\033[34m OK\033[0m"

$(OBJ_DIR)/%.o: $(EXE_DIR)/%.c
	@$(CC) -o $@ -c $< $(INC) $(FLAGS)
	@echo "\033[0m\033[36m$(notdir $<)\033[1m\033[34m OK\033[0m"

$(OBJ_DIR)/%.o: $(UT_DIR)/%.c
	@$(CC) -o $@ -c $< $(INC) $(FLAGS)
	@echo "\033[0m\033[36m$(notdir $<)\033[1m\033[34m OK\033[0m"

$(OBJ_DIR)/%.o: $(BIN_DIR)/%.c
	@$(CC) -o $@ -c $< $(INC) $(FLAGS)
	@echo "\033[0m\033[36m$(notdir $<)\033[1m\033[34m OK\033[0m"

clean:
		@make clean -s -C $(LIB_DIR)
		@rm -f $(OBJ)

fclean: clean
		@make fclean -s -C $(LIB_DIR)
		@find . -type f -name ".*.swp" -exec rm -f {} \;
		@rm -rf *test*
		@rm -rf $(NAME)*

re:	fclean all

.PHONY: all, clean, fclean, re
