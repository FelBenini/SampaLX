# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbenini- <your@mail.com>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/11 18:28:31 by fbenini-          #+#    #+#              #
#    Updated: 2025/10/14 14:37:58 by fbenini-         ###   ########.fr        #
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

SRCS = ./src/mlx_init.c \
	   ./src/mlx_destroy_display.c \
	   ./src/mlx_loop.c \
	   ./src/mlx_loop_hook.c \
	   ./src/mlx_new_window.c \
	   ./src/mlx_dispatchers.c \
	   ./src/mlx_shaders.c \
	   ./src/mlx_get_data_addr.c \
	   ./src/mlx_new_image.c \
	   ./src/mlx_put_image_to_window.c \
	   ./src/mlx_destroy_window.c \
	   ./src/mlx_hook.c

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
