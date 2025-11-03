/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 18:22:37 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/27 18:00:46 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_INT_H
# define MLX_INT_H

# include "mlx.h"
# include "mlx_font.h"
# include "../glad/include/glad/glad.h"
# include "mlx_int_hooks.h"
# include <GLFW/glfw3.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct s_hook_info
{
	int			(*hook)();
	void		*param;
	long		mask;
}	t_hook_info;

typedef struct s_window
{
	unsigned int	vbo;
	unsigned int	vao;
	unsigned int	ebo;
	unsigned int	shader_program;
	char			*win_title;
	int				width;
	int				height;
	struct s_window	*next; // linked list to handle multiple windows
	GLFWwindow		*glfw_window;
	t_hook_info		hooks[MLX_MAX_EVENTS];
}	t_window;

typedef struct s_img
{
	unsigned char	*data;
	unsigned char	*final_texture;
	unsigned int	texture_id;
	int				width;
	int				height;
	int				line_len;
	int				endian;
	int				bits_per_pixel;
}	t_img;

typedef struct s_mlx
{
	t_window	*win_list;
	int			(*loop_hook)(void *param);
	void		*loop_param;
	int			is_loop_end;
}	t_mlx;

typedef struct s_keymap
{
	int	glfw_keycode;
	int	mlx_keycode;
}	t_keymap;

unsigned int	_create_shader_program(void);
int				_glfw_to_mlx_keycode(int glfw_keycode);
int				_glfw_mouse_to_mlx(int glfw_keycode);
void			_set_pos_and_size_of_texture(t_window *window, t_img *img,
											int x, int y);

#endif
