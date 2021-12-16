# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/15 23:56:37 by lpaulo-d          #+#    #+#              #
#    Updated: 2021/12/16 23:01:27 by lpaulo-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

P_SRC			=	src/
P_INCLUDE		=	include/
P_UTILS			=	utils/
P_BUILTINS		=	builtins/
P_OBJ			=	./obj/

FT				=	ft
P_LIBFT			=	$(P_INCLUDE)libft/


F_SRC			=	main.c $(UTILS)

F_BUILTINS		=	save_env.c cd_input.c

F_UTILS			=	do_free.c list_aux.c aux_0.c parse_input.c $(BUILTINS)

BUILTINS		=	$(addprefix $(P_BUILTINS), $(F_BUILTINS))
UTILS			=	$(addprefix $(P_UTILS), $(F_UTILS))

OBJ				=	$(addprefix $(P_OBJ), $(F_SRC:.c=.o))

NAME			=	minishell

INC				=	-I $(P_INCLUDE) -I $(P_LIBFT)
LIBFT			=	-L $(P_LIBFT) -l $(FT)#$(P_LIBFT)libft.a
CFLAGS			=	-Wall -Wextra -Werror
P_GUARD			=	mkdir -p $(@D)
RM				=	rm -rf
CC				=	clang

all:			$(NAME)

$(NAME):		$(OBJ)
				@make --no-print-directory -C $(P_LIBFT)
				@echo '.o created and moved to obj folder'
				@$(CC) -g -lreadline $(INC) $(OBJ) $(LIBFT) -o $(NAME)
				@echo 'File(minishell) created'

$(P_OBJ)%.o:	$(P_SRC)%.c
				@$(P_GUARD)
				@$(CC) -g $(INC) -c $< -o $@

clean:
				@$(RM) $(P_OBJ)
				@make --no-print-directory -C $(P_LIBFT) clean

fclean:			clean
				@$(RM) $(NAME)
				@make --no-print-directory -C $(P_LIBFT) fclean

re:				fclean all

add:	fclean
	git add .
	git commit -m "Start parse input (cd)"

push:	add
	git push

.PHONY:			all clean fclean re add push
