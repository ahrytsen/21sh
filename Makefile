#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/30 18:43:03 by ahrytsen          #+#    #+#              #
#    Updated: 2018/03/17 18:17:17 by ahrytsen         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	minishell
DIRSRC		=	./src/
DIROBJ		=	./obj/
INCLUDE		=	-I./inc/ -I./libft/
SUB_MAKE	=	./libft/
SUB_OBJ		=	libftprintf.a
INC_LIB		=	-L./libft -lftprintf -ltermcap
SRC			=	minishell.c builtins.c env_builtin.c env_utils.c exec.c error.c	\
				cmd_parser.c ft_buffer.c msh_splitsemicolon.c ft_cd.c			\
				msh_splitwhitespaces.c quote_helper.c line_parser.c cmdline.c	\
				ft_readline.c
HDR			=	inc/minishell.h
LIBFT		=	libft/libftprintf.a
OBJ			=	$(addprefix $(DIROBJ), $(SRC:.c=.o))

ifdef FLAGS
	ifeq ($(FLAGS), no)
CFLAGS		=
	endif
	ifeq ($(FLAGS), debug)
CFLAGS		=	-Wall -Wextra -Werror -pedantic -g
	endif
else
CFLAGS		=	-Wall -Wextra -Werror
endif

CC			=	gcc
RM			=	rm -rf
ECHO		=	echo

all		:		lib $(NAME)

$(NAME)	:		$(DIROBJ) $(OBJ) $(LIBFT)
				@$(CC) $(INCLUDE) $(INC_LIB) $(CFLAGS) -O3 -o $(NAME) $(OBJ)
				@$(ECHO) "\033[31m> \033[32mminishell: Compiled\033[0m"

lib		:
				@$(MAKE) -C $(SUB_MAKE) -j3

$(LIBFT):		lib

clean	:
				@($(RM) $(DIROBJ))
ifdef SUB_MAKE
				@$(MAKE) -C $(SUB_MAKE) clean
endif
				@$(ECHO) "\033[31m> \033[33mminishell: Directory cleaned\033[0m"



fclean	:		clean
ifdef SUB_MAKE
				@$(MAKE) -C $(SUB_MAKE) fclean
endif
				-@$(RM) $(NAME)
				@$(ECHO) "\033[31m> \033[33mminishell: Remove executable\033[0m"

re		:		fclean all

.PHONY	:		all clean re

$(DIROBJ):
				@mkdir $(DIROBJ)

$(OBJ)	:		$(DIROBJ)%.o : $(DIRSRC)%.c $(HDR)
				@$(CC) $(INCLUDE) $(CFLAGS) -O3 -o $@ -c $<
