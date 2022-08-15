# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/10 00:54:23 by sungjpar          #+#    #+#              #
#    Updated: 2022/08/15 15:28:53 by sungjpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = echo

INC_DIR = ./include/

SRC_DIR = ./src/

INC_FLAG = -I$(INC_DIR)

SRC_FILES = $(addprefix $(SRC_DIR),\
			echo.c\
			echo_string.c\
			get_option.c\
			run_program.c\
)

OBJ = ${SRC_FILES:.c=.o}

all 	: $(NAME)

$(NAME)	: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(INC_FLAG)

%.o 	: %.c
	$(CC) $(CFLAGS) $(INC_FLAG) -c $< -o $@

clean	:
	rm -f $(OBJ)

fclean	:
	rm -f $(NAME)
	$(MAKE) clean

re		:
	$(MAKE) fclean
	$(MAKE) all

.PHONY	: clean fclean re all
