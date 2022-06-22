# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsellars <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/22 12:08:44 by jsellars          #+#    #+#              #
#    Updated: 2022/06/22 12:15:33 by jsellars         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
FLAGS = -g -Wall -Wextra -Werror

SRC = philosophers.c

all: $(NAME)

$(NAME):
	@$(CC) $(FLAGS) -pthread $(SRC) -o $(NAME)

clean:
	@rm -f $(NAME)

fclean: clean

re:
	@$(MAKE) fclean all -C ./$(NAME)

.PHONY: all clean fclean re
