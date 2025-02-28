# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmacau <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 16:50:35 by fmacau            #+#    #+#              #
#    Updated: 2025/02/28 08:44:55 by fmacau           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo
CC = cc 
FLAGS = -Wall -Wextra -Werror
SRC = ./philo.c \
	 ./ft_checker.c \
	 ./utils/ft_atoi.c \
	 ./utils/ft_isdigit.c \
	 ./utils/ft_stop.c \
	 ./ft_parse_args.c \
	 ./ft_init_data.c \
	 ./utils/ft_current_time.c \
	 ./log_message.c \
	 ./actions.c \
	 ./simulation.c \
	 ./clean_all.c \
	 ./supervisor.c \

OBJ = ${SRC:.c=.o}


${NAME}: $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -Iincludes -o $(NAME)
	@echo "compiled"
%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

clean: 
	@rm -rf $(OBJ)
	@echo "clean objects files..."

fclean:
	@rm -rf $(NAME)
	@echo "remove file ./philo"

re: fclean all
