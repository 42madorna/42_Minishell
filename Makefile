# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madorna- <madorna-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 00:55:04 by madorna-          #+#    #+#              #
#    Updated: 2021/11/26 17:45:59 by madorna-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c																	\
		ft_execve.c																\
		builtin/ft_exit.c														\
		builtin/builtin.c														\
		parser/parse.c

# builtin/ft_cd.c														
# builtin/ft_echo.c														
# builtin/ft_env.c														
# builtin/ft_export.c													
# builtin/ft_pwd.c														
# builtin/ft_uknset.c													

NAME = minishell

NAME 			=	minishell

OBJS			= 	$(SRCS:.c=.o)

NAME_LIBFT		=	libft.a
PATH_LIBFT		=	libft
LIBFT			=	$(PATH_LIBFT)/$(NAME_LIBFT)

INCLUDES		=	-I. -I$(PATH_LIBFT) -Ibuiltin

PATH_LIBS		=	-L$(PATH_LIBFT)

ifeq ($(shell uname -s),Darwin)
	INCLUDES += -I/Users/$(USER)/.brew/opt/readline/include
	PATH_LIBS += -L/Users/$(USER)/.brew/opt/readline/lib
endif
###-L searchdir
###--library-path=searchdir
# Añade la ruta "searchdir" a la lista de rutas que buscará para bibliotecas y
# scripts de control

LIBS			=	-lft -lreadline
###-l namespec
###--library=namespec
# Añade el archivo u objeto especificado por "namespec" a la lista de ficheros
# a linkar. Si "namespec" es de la forma ':filename', buscará la ruta de la
# biblioteca para un fichero llamado filename, sino buscará la ruta de la
# biblioteca para un fichero llamado 'libnamespec.a' (poniendo el sufijo lib
# antes del nombre pasado)

CC 				=	gcc

RM 				=	rm -f

SANITIZE		=	-fsanitize=address -g3 -O0

CFLAGS 			=	$(INCLUDES) -Wall #-Wextra -Werror

LDFLAGS 		=	$(PATH_LIBS) $(LIBS)

#.c.o:
#		@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

$(NAME):	$(LIBFT) $(OBJS)
				$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

$(LIBFT):
				make -C $(PATH_LIBFT) bonus
#-C -->Cambia al directorio PATH_LIBFT antes de leer la orden,
#y es en ese directorio donde ejecuta lo pedido
#Normalmente se usa con invocaciones recursivas de make

all:		$(NAME)

print:
	echo $(PATH_LIBFT)

clean:
				$(RM) $(OBJS)

fclean:		clean
				@$(RM) $(NAME)
				@make -C $(PATH_LIBFT) fclean

re:			fclean all

rebug:		fclean debug

debug:		$(NAME)
debug:		CFLAGS += $(SANITIZE)
debug:		LDFLAGS += $(SANITIZE)

#.SILENT:	all clean fclean re $(NAME)
.PHONY:		all clean fclean re debug