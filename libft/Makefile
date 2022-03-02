# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 18:17:32 by agaliste          #+#    #+#              #
#    Updated: 2022/03/02 14:06:54 by agaliste         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =	char_manipulation/ft_tolower.c											\
		char_manipulation/ft_toupper.c											\
		checkers/ft_isdigit.c													\
		checkers/ft_isprint.c													\
		checkers/ft_isalnum.c													\
		checkers/ft_isalpha.c													\
		checkers/ft_isascii.c													\
		converters/ft_atoi.c													\
		converters/ft_atoli.c													\
		converters/ft_itoa.c													\
		general_purpose/ft_putchar_fd.c											\
		general_purpose/ft_putstr_fd.c											\
		general_purpose/ft_putendl_fd.c											\
		general_purpose/ft_putnbr_fd.c											\
		general_purpose/ft_gnl.c												\
		linked_list/ft_lstnew.c													\
		linked_list/ft_lstadd_front.c											\
		linked_list/ft_lstsize.c												\
		linked_list/ft_lstlast.c												\
		linked_list/ft_lstadd_back.c											\
		linked_list/ft_lstdelone.c												\
		linked_list/ft_lstclear.c												\
		linked_list/ft_lstiter.c												\
		linked_list/ft_lstmap.c													\
		linked_list/ft_lstdel_last.c											\
		memory_manipulation/ft_memset.c											\
		memory_manipulation/ft_calloc.c											\
		memory_manipulation/ft_memchr.c											\
		memory_manipulation/ft_memcmp.c											\
		memory_manipulation/ft_bzero.c											\
		memory_manipulation/ft_memccpy.c										\
		memory_manipulation/ft_memcpy.c											\
		memory_manipulation/ft_memmove.c										\
		memory_manipulation/ft_free_matrix.c									\
		memory_manipulation/ft_realloc.c										\
		string_manipulation/ft_strlcat.c										\
		string_manipulation/ft_strlcpy.c										\
		string_manipulation/ft_strlen.c											\
		string_manipulation/ft_strncmp.c										\
		string_manipulation/ft_strchr.c											\
		string_manipulation/ft_strnstr.c										\
		string_manipulation/ft_strdup.c											\
		string_manipulation/ft_strrchr.c										\
		string_manipulation/ft_substr.c											\
		string_manipulation/ft_strjoin.c										\
		string_manipulation/ft_strtrim.c										\
		string_manipulation/ft_strmapi.c										\
		string_manipulation/ft_split.c											\
		string_manipulation/ft_split.c											\
		string_manipulation/ft_strcmp.c
		

OBJS = ${SRCS:.c=.o}

INCLUDES = -I.

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} ${INCLUDES} -g -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
		ar rcs ${NAME} ${OBJS}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

all: ${NAME} ${OBJS}

re:		fclean all
