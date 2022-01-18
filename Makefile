# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/15 23:56:37 by lpaulo-d          #+#    #+#              #
#    Updated: 2022/01/18 17:07:27 by lpaulo-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

P_SRC			=	src/
P_INCLUDE		=	include/
P_AUX			=	aux/
P_PARSE			=	parse/
P_BUILTINS		=	builtins/
P_OBJ			=	./obj/

FT				=	ft
P_LIBFT			=	$(P_INCLUDE)libft/

F_PARSE			=	parse_input.c

F_BUILTINS		=	env.c cd.c signal.c pwd.c export.c unset.c echo.c execve.c

F_AUX			=	do_free.c aux_0.c aux_treatment.c treatment.c errors.c \
					aux_1.c find_redirect.c handle_fd.c

F_SRC			=	main.c $(AUX) $(BUILTINS) $(PARSE)

BUILTINS		=	$(addprefix $(P_BUILTINS), $(F_BUILTINS))
PARSE			=	$(addprefix $(P_PARSE), $(F_PARSE))
AUX				=	$(addprefix $(P_AUX), $(F_AUX))

OBJ				=	$(addprefix $(P_OBJ), $(F_SRC:.c=.o))

NAME			=	minishell

INC				=	-I $(P_INCLUDE) -I $(P_LIBFT)
LIBFT			=	-L $(P_LIBFT) -l $(FT) 		#$(P_LIBFT)libft.a
CFLAGS			=	-Wall -Wextra -Werror #-fsanitize=address
P_GUARD			=	mkdir -p $(@D)
RM				=	rm -rf
CC				=	clang

all:			$(NAME)

$(NAME):		$(OBJ)
				@make --no-print-directory -C $(P_LIBFT)
				@echo '.o created and moved to obj folder'
				@$(CC) $(CFLAGS) -g -lreadline $(INC) $(OBJ) $(LIBFT) -o $(NAME)
				@echo 'File(minishell) created'

$(P_OBJ)%.o:	$(P_SRC)%.c
				@$(P_GUARD)
				@$(CC) $(CFLAGS) -g $(INC) -c $< -o $@

val:
				valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes --trace-children=yes --suppressions=readline.supp --log-file=valgrind-out.txt ./minishell

clean:
				@$(RM) $(P_OBJ)
				@make --no-print-directory -C $(P_LIBFT) clean
				@echo 'All clean dude'

fclean:			clean
				@$(RM) $(NAME)
				@$(RM) vgcore* #remover depois
				@$(RM) valgrind* #remover depois
				@make --no-print-directory -C $(P_LIBFT) fclean

re:				fclean all

.PHONY:			all clean fclean val
