# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsellars <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/22 12:08:44 by jsellars          #+#    #+#              #
#    Updated: 2022/08/14 20:19:31 by jsellars         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
FLAGS = -g -pthread -Wall -Wextra -Werror

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
