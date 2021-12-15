#Try new method

NAME			=	minishell

P_SRC			=	./src/
P_INCLUDE		=	./include/
P_UTILS			=	$(P_SRC)utils/
P_BUILTINS		=	$(P_UTILS)builtins/
P_LINKED_LIST	=	$(P_UTILS)linked_list/
P_LIBFT			=	$(P_INCLUDE)libft/
LIBFT			=	$(P_LIBFT)libft.a
P_OBJ			=	./obj/

FILES			=	$(P_SRC)main.c \
					$(P_BUILTINS)save_env.c \
					$(P_UTILS)deal_error.c \
					$(P_LINKED_LIST)list_aux.c

SRC				=	$(patsubst $(P_SRC)%.c, $(P_OBJ)%.o, $(FILES))

CC				=	gcc
RM				=	rm -rf
CFLAGS			=	-Wall -Werror -Wextra
INC				=	-I $(P_INCLUDE) -I $(P_LIBFT)
SAN				=	-g -fsanitize=address

all:	$(NAME)

$(NAME):	$(SRC)
			@make --no-print-directory -C $(P_LIBFT)
			@echo Folder for obj Created.
			@$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME)
			@echo 'File(minishell) created.'

$(P_OBJ)%.o:	$(P_SRC)%.c
				@mkdir -p $(P_OBJ)
				@mkdir -p $(P_OBJ)utils
				@mkdir -p $(P_OBJ)utils/builtins
				@mkdir -p $(P_OBJ)utils/linked_list
				$(CC) $(CFLAGS) $(INC) -c $< -o $@

#VALGRIND--|
#val:
#	valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes --log-file=valgrind-out.txt ./$(NAME) $(a)

clean:
	@$(RM) $(P_OBJ)
	@make clean --no-print-directory -C $(P_LIBFT)
#	@rm -f valgrind-out.txt
	@echo All clean.

fclean: clean
	@$(RM) $(NAME)
	@make fclean --no-print-directory -C $(P_LIBFT)

re: fclean all
