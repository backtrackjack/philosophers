# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsellars <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/22 12:08:44 by jsellars          #+#    #+#              #
#    Updated: 2022/08/10 21:53:16 by jsellars         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
FLAGS = -g -Wall -Wextra -Werror

SRC = philo.c init.c thread.c

all: $(NAME)

$(NAME):
	@$(CC) $(FLAGS) -pthread $(SRC) -o $(NAME)

clean:
	@rm -f $(NAME)

fclean: clean

re:
	@$(MAKE) fclean all 

.PHONY: all clean fclean re
