# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aitorres <aitorres@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/30 17:32:47 by aitorres          #+#    #+#              #
#    Updated: 2026/02/04 13:49:35 by aitorres         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN := \033[0;32m

RED := \033[31m

NAME	=	libftprintf.a

SRC		=	ft_printf.c\
			ft_printf_c_s.c\
			ft_printf_d_i.c\
			ft_printf_p.c\
			ft_printf_u.c\
			ft_printf_x_x.c


OBJ		=	$(SRC:.c=.o)

AR		=	ar rcs
CC		=	cc
FLAGS	=	-Wall -Werror -Wextra

all:		$(NAME)	#crea la librería con todos los objetos

$(NAME):	$(OBJ)
			@$(AR) $(NAME) $(OBJ)
			@echo "${GREEN} $(NAME) creado."

%.o:		%.c	#para compilar cualquier .c a .o
			@$(CC) $(FLAGS) -c $< -o $@

clean:		
			@rm -f $(OBJ)
			@echo "${RED} Objetos eliminados."
			
fclean:		clean
			@rm -f $(NAME)
			@echo "${RED} Librería eliminada."

re:			fclean	all	#recompila desde cero

.PHONY: all clean fclean re

TOTAL = 10

# make        # Compila todo
# make clean  # Borra objetos
# make fclean # Borra objetos y librería
# make re     # Limpia y recompila