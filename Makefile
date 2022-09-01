# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/10 00:54:23 by sungjpar          #+#    #+#              #
#    Updated: 2022/09/01 17:48:47 by sungjpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

NAME = minishell

INC_DIR = ./include/

SRC_DIR = ./src/

LFT_DIR = ./library/libft

BUITIN_DIR = ./builtin_programs

ECHO_DIR = $(BUITIN_DIR)/echo/

LIB_FLAG = -L $(LFT_DIR) -lft\
		   -L$(HOME)/.brew/opt/readline/lib\
		   -lreadline

INC_FLAG = -I$(INC_DIR)\
		   -I$(LFT_DIR)/include\
		   -I$(HOME)/.brew/opt/readline/include

SRC_FILES = $(addprefix $(SRC_DIR),\
			binary_tree/bst_clear_tree.c\
			binary_tree/bst_get_root.c\
			binary_tree/bst_delete_node.c\
			binary_tree/bst_create_node.c\
			binary_tree/bst_insert_node.c\
			binary_tree/bst_link_right_child.c\
			binary_tree/bst_link_left_child.c\
			error_control_functions/e_close.c\
			error_control_functions/e_dup2.c\
			error_control_functions/e_fork.c\
			error_control_functions/e_malloc.c\
			error_control_functions/e_open.c\
			error_control_functions/e_pipe.c\
			executer/analyze_and_execute_command.c\
			executer/executer.c\
			executer/executer_node_utils.c\
			executer/executer_token_funcs.c\
			executer/executer_utils.c\
			executer/explore_tree_and_execute_command.c\
			executer/pipe_utils.c\
			executer/run_heredoc.c\
			executer/run_command.c\
			heredoc/heredoc.c\
			parser/index_skip_functions.c\
			parser/check_valid_ast.c\
			parser/lexer.c\
			parser/lexer_utils.c\
			parser/parser.c\
			parser/parser_utils.c\
			parser/merge_arguments_in_ast.c\
			replacer/back_slash_replacer.c\
			replacer/double_quote_replacer.c\
			replacer/env_replacer.c\
			replacer/get_replaced_string_size.c\
			replacer/copy_string.c\
			replacer/replacer.c\
			replacer/single_quote_replacer.c\
			env_substituter/env_substituter.c\
			env_substituter/env_substituter_utils.c\
			utils/stat_check.c\
			utils/has_space.c\
			utils/find_execute_file_path.c\
			utils/free_strings.c\
			utils/free_token.c\
			utils/is_symbol.c\
			utils/sigint_handler.c\
			utils/change_envp_value.c\
			prompt/prompt.c\
			prompt/print_main_page.c\
			builtin_function/builtin_cd.c\
			builtin_function/builtin_env.c\
			builtin_function/builtin_exit.c\
			builtin_function/builtin_export.c\
			builtin_function/builtin_export_utils.c\
			builtin_function/builtin_pwd.c\
			builtin_function/builtin_unset.c\
			main.c\
)

OBJS = ${SRC_FILES:.c=.o}

all 	: $(NAME)

subsystem :
	$(MAKE) -C $(LFT_DIR)
	$(MAKE) -C $(ECHO_DIR)

$(NAME)	: subsystem $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAG) -o $(NAME) $(INC_FLAG)

%.o 	: %.c
	$(CC) $(CFLAGS) $(INC_FLAG) -c $< -o $@

clean	:
	rm -f $(OBJS)
	$(MAKE) -C $(LFT_DIR) clean
	$(MAKE) -C $(ECHO_DIR) clean

fclean	:
	rm -f $(NAME)
	$(MAKE) clean
	$(MAKE) -C $(LFT_DIR) fclean
	$(MAKE) -C $(ECHO_DIR) fclean

re		: fclean
	$(MAKE) all

.PHONY	: clean fclean re all subsystem
