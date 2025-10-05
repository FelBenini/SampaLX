# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbenini- <your@mail.com>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/05 05:23:30 by fbenini-          #+#    #+#              #
#    Updated: 2025/10/05 05:50:11 by fbenini-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = "libmlx.a"

SRCS = ./src/mlx_init.c

OBJS = $(SRCS:%.c=%.o)

CFLAGS = -Wall -Wextra -Werror -O3

CC = cc

AR = ar rcs

GLAD = ./glad/libglad.a

GLAD_SRCS = ./glad/src/glad.c

GLAD_OBJS = $(GLAD_SRCS:.c=.o)

$(NAME): $(OBJS) $(GLAD)
	mv $(GLAD) $(NAME)
	$(AR) $(NAME) $(OBJS)

$(GLAD): $(GLAD_OBJS)
	$(AR) $(GLAD) $(GLAD_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(GLAD_OBJS)
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

.PHONY: all clean fclean
