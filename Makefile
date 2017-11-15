# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 11:49:36 by iprokofy          #+#    #+#              #
#    Updated: 2017/11/15 15:36:18 by iprokofy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRC = *.c
LIBFT = libft/*.c ft_printf/*.c
FLAGS = -Wall -Wextra -Werror

all: $(SRC) 
	gcc $(FLAGS) $(SRC) $(LIBFT) -o $(NAME)