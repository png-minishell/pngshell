# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/10 00:54:23 by sungjpar          #+#    #+#              #
#    Updated: 2022/08/15 15:26:50 by sungjpar         ###   ########.fr        #
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

LIB_FLAG = -L $(LFT_DIR) -ft

INC_FLAG = -I$(INC_DIR)\
		   -I$(LFT_DIR)/include\

SRC_FILES = $(addprefix $(SRC_DIR),\
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
