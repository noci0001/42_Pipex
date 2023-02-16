# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 17:31:46 by snocita           #+#    #+#              #
#    Updated: 2023/02/16 14:33:51 by snocita          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf

HEADER	= pipex.h

SRCS	= pipex.c subprocesses.c freeprocesses.c error.c
OBJS	= $(SRCS:.c=.o)
OBJ_DIR = obj

INOUT	= InOut

LIBFT_PATH	= ./LIBFT
LIBFT		= $(LIBFT_PATH)/libft.a

%.o: %.c
		${CC} ${CFLAGS} -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJ_DIR) $(OBJS) $(LIBFT) $(INOUT)
			cp $(LIBFT) .
			@$(CC) $(CFLAGS) $(OBJS) libft.a -o $(NAME)
			mv *.o ./obj

$(OBJ_DIR):
			mkdir $(OBJ_DIR)

$(INOUT):
			mkdir $(INOUT)
			touch InOut/infile.txt InOut/outfile.txt
			echo "THE\nQUICK\nBROWN\nFOX\n" > InOut/infile.txt

$(LIBFT):
			make -C $(LIBFT_PATH) all


clean:
		@$(RM) obj/
		@$(RM) InOut/*
		@$(RM) InOut
		make -C $(LIBFT_PATH) clean

fclean:	clean
		@$(RM) $(NAME)
		$(RM) libft.a
		make -C $(LIBFT_PATH) fclean

re:		fclean all