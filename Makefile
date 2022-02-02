# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/15 23:56:37 by lpaulo-d          #+#    #+#              #
#    Updated: 2022/02/01 21:31:14 by lpaulo-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

P_SRC			=	src/
P_INCLUDE		=	include/
P_AUX			=	aux/
P_UTILS			=	utils/
P_PARSE			=	parse/
P_BUILTINS		=	builtins/
P_OBJ			=	./obj/

FT				=	ft
P_LIBFT			=	$(P_INCLUDE)libft/

F_PARSE			=	parse_input.c

F_BUILTINS		=	env.c cd.c pwd.c export.c unset.c echo.c execve.c

F_AUX			=	do_free.c treatment.c signal.c redirect.c pipe.c

F_UTILS			=	aux_0.c aux_treatment.c aux_1.c cut_check.c aux_2_redic.c \
					aux_redirect.c aux_free.c

F_SRC			=	main.c $(AUX) $(BUILTINS) $(UTILS) $(PARSE)

BUILTINS		=	$(addprefix $(P_BUILTINS), $(F_BUILTINS))
PARSE			=	$(addprefix $(P_PARSE), $(F_PARSE))
AUX				=	$(addprefix $(P_AUX), $(F_AUX))
UTILS			=	$(addprefix $(P_AUX)$(P_UTILS), $(F_UTILS))

OBJ				=	$(addprefix $(P_OBJ), $(F_SRC:.c=.o))

NAME			=	minishell

INC				=	-I $(P_INCLUDE) -I $(P_LIBFT)
LIBFT			=	-L $(P_LIBFT) -l $(FT)
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

child:
				valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes --suppressions=readline.supp --log-file=valgrind-out.txt ./minishell

clean:
				@$(RM) $(P_OBJ)
				@make --no-print-directory -C $(P_LIBFT) clean
				@echo 'All clean dude'

fclean:			clean
				@$(RM) $(NAME)
				@$(RM) vgcore*
				@$(RM) valgrind*
				@make --no-print-directory -C $(P_LIBFT) fclean

re:				fclean all

.PHONY:			all clean fclean val
