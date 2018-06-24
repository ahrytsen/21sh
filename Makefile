#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/30 18:43:03 by ahrytsen          #+#    #+#              #
#    Updated: 2018/06/24 17:02:46 by ahrytsen         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	21sh
DIRSRC		=	./src/
DIROBJ		=	./obj/
INCLUDE		=	-I./inc/ -I./libft/includes
SUB_MAKE	=	./libft/
SUB_OBJ		=	libftprintf.a
INC_LIB		=	-L./libft -lftprintf -ltermcap

SRC			=	main.c init.c env_utils.c ft_buffer.c ft_signal.c			\
				ft_tokenize.c ft_tokenize_utils.c ft_ast.c ft_ast_utils.c	\
				ft_ast_exec.c ft_cmdlst.c ft_cmdlst_utils.c ft_cmdlst_exec.c\
				ft_argv.c ft_argv_utils.c ft_argv_quotes.c ft_argv_exec.c	\
				ft_redirection.c ft_redirection_utils.c ft_heredoc.c		\
				ft_wait.c													\
				\
				builtins/builtins.c builtins/env_builtin.c builtins/ft_cd.c	\
				\
				ft_readline/ft_autocomplit.c ft_readline/ft_readline.c		\
				ft_readline/ft_readline_action.c ft_readline/line.c			\
				ft_readline/ft_cursor.c ft_readline/ft_readline_helper.c	\
				ft_readline/ft_history.c ft_readline/ft_highlight.c			\
				ft_readline/line_edit.c ft_readline/ft_prompt.c 			\
				ft_readline/ft_check_line.c

HDR			=	inc/twenty_one_sh.h
LIBFT		=	libft/libftprintf.a
OBJ			=	$(addprefix $(DIROBJ), $(SRC:.c=.o))

ifdef FLAGS
	ifeq ($(FLAGS), no)
CFLAGS		=
	endif
	ifeq ($(FLAGS), debug)
CFLAGS		=	-Wall -Wextra -Werror -g
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
				@$(ECHO) "\033[31m> \033[32m"$(NAME)": Compiled\033[0m"

lib		:
				@$(MAKE) -C $(SUB_MAKE) -j3

$(LIBFT):		lib

clean	:
				@($(RM) $(DIROBJ))
ifdef SUB_MAKE
				@$(MAKE) -C $(SUB_MAKE) clean
endif
				@$(ECHO) "\033[31m> \033[33m"$(NAME)": Directory cleaned\033[0m"



fclean	:		clean
ifdef SUB_MAKE
				@$(MAKE) -C $(SUB_MAKE) fclean
endif
				-@$(RM) $(NAME)
				@$(ECHO) "\033[31m> \033[33m"$(NAME)": Remove executable\033[0m"

re		:		fclean all

.PHONY	:		all clean re

$(DIROBJ):
				@mkdir -p $(DIROBJ)
				@mkdir -p $(DIROBJ)/builtins
				@mkdir -p $(DIROBJ)/ft_readline

$(OBJ)	:		$(DIROBJ)%.o : $(DIRSRC)%.c $(HDR)
				@$(CC) $(INCLUDE) $(CFLAGS) -O3 -o $@ -c $<
