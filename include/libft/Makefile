# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/16 00:11:49 by lpaulo-d          #+#    #+#              #
#    Updated: 2022/01/28 18:15:56 by lpaulo-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

P_MANDATORY	=	mandatory/
P_OBJ		=	./obj/

F_MANDATORY	=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
				ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
				ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
				ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
				ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c \
				ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
				ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
				ft_putnbr_fd.c

SRC			=	$(MANDATORY)

MANDATORY	=	$(addprefix $(P_MANDATORY), $(F_MANDATORY))

OBJ			=	$(addprefix $(P_OBJ), $(SRC:.c=.o))

NAME		=	libft.a

INC			=	-I .
CFLAGS		=	-Wall -Wextra -Werror
P_GUARD		=	mkdir -p $(@D)
RM			=	rm -rf
CC			=	clang

all:			$(NAME)

$(NAME):		$(OBJ)
				@ar -rcs $(NAME) $(OBJ)
				@echo 'libft.a created'

${P_OBJ}%.o:	%.c
				@${P_GUARD}
				@${CC} ${CFLAGS} ${INC} -c $< -o $@

clean:
				@$(RM) $(P_OBJ)

fclean:			clean
				@$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
