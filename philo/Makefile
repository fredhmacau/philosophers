# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmacau <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 16:50:35 by fmacau            #+#    #+#              #
#    Updated: 2025/02/27 20:05:47 by fmacau           ###   ########.fr        #
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

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@


${NAME} : $(OBJ)
		$(CC) $(FLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean: 
	@rm -f $(OBJ)

fclean:
	@rm -f $(NAME)

re: clean all
