# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpetit <gpetit@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/06 16:53:31 by gpetit            #+#    #+#              #
#    Updated: 2021/08/19 14:33:24 by gpetit           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo

CC= clang

CFLAGS= -Wall -Wextra -Werror -g3 -fsanitize=thread

SRCS= $(addprefix srcs/, main.c utils.c utils2.c parsing.c philo.c clock.c \
	threads.c tamagochi_actions.c)

OBJS= $(SRCS:.c=.o)

INCLUDE= includes/

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $^ -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
