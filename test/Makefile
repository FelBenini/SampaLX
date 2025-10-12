# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbenini- <your@mail.com>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/05 06:33:27 by fbenini-          #+#    #+#              #
#    Updated: 2025/10/05 07:12:55 by fbenini-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = program

CC = cc

CFLAGS = -Wall -Wextra -Werror -O3 -I../ -lGL -lglfw

SRCS = ./main.c

OBJS = $(SRCS:.c=.o)

LIBMLX = ../libmlx.a

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) ../minilibx.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all re fclean clean
