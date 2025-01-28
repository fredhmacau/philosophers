# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmacau <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 16:50:35 by fmacau            #+#    #+#              #
#    Updated: 2025/01/28 16:50:38 by fmacau           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo
CC = cc 
FLAGS = -Wall -Wextra -Werror
SRC = ./philo.c \
	 ./ft_checker.c \

OBJ = ${SRC:.c=.o}

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@


${NAME} : $(OBJ)
		$(CC) $(FLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean: 
	@rm -f $(OBJ)

fclean:
	@rm -f $(NAME)

re: fclean all
