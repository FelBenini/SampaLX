# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbenini- <your@mail.com>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/11 18:28:31 by fbenini-          #+#    #+#              #
#    Updated: 2025/10/14 15:16:07 by fbenini-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = "minilibx.a"

CC = cc

AR = ar rcs

CFLAGS = -Wall -Wextra -Werror

ENDFLAGS = -lglfw -lGL

GLAD = ./glad/libglad.a

GLADSRCS = ./glad/src/glad.c

GLADOBJS = $(GLADSRCS:.c=.o)

SRCS = $(wildcard ./src/*.c)

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS) $(GLAD)
	mv $(GLAD) $(NAME)
	$(AR) $(NAME) $(OBJS) $(GLADOBJS)

$(GLAD): $(GLADOBJS)
	$(AR) $(GLAD) $(GLADOBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJS) $(GLADOBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: re clean fclean all
