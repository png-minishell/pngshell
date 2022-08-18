# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/10 00:54:23 by sungjpar          #+#    #+#              #
#    Updated: 2022/08/18 14:51:40 by sungjpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = minishell

INC_DIR = ./include/

SRC_DIR = ./src/

LFT_DIR = ./library/libft

BUITIN_DIR = ./builtin_programs

ECHO_DIR = $(BUITIN_DIR)/echo/

LIB_FLAG = -L $(LFT_DIR) -lft

INC_FLAG = -I$(INC_DIR)\
		   -I$(LFT_DIR)/include\

SRC_FILES = $(addprefix $(SRC_DIR),\
			binary_tree/bst_clear_tree.c\
			binary_tree/bst_get_root.c\
			binary_tree/bst_delete_node.c\
			binary_tree/bst_create_node.c\
			binary_tree/bst_insert_node.c\
			binary_tree/bst_link_right_child.c\
			binary_tree/bst_link_left_child.c\
			error_control_functions/e_malloc.c\
			parser/index_skip_functions.c\
			parser/lexer.c\
			parser/lexer_utils.c\
			parser/parser.c\
			parser/parser_utils.c\
			parser/parser_tester.c\
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
