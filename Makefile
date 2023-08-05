# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eportela <eportela@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/02 16:38:50 by eportela          #+#    #+#              #
#    Updated: 2023/08/05 21:26:34 by eportela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

CFLAGS = -pthread -Wall -Wextra -Werror -g -fsanitize=thread

CFILES = src/philo.c utils/aux_f.c utils/errors.c utils/system.c \
			src/threads.c src/actions.c src/engine.c utils/cleaners.c\

OBJECTS = $(CFILES:.c=.o)

all: $(NAME)

%.o : %.c
	@$(CC) -Iinclude $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
	@rm -f $(OBJECTS)

fclean:		clean
	@rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
