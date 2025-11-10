/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_string_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 19:56:05 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/28 14:18:28 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdint.h>
#define BPP sizeof(int32_t)

static void mlx_draw_char(t_img* image, int32_t texoffset, int32_t imgoffset, int color)
{
	uint8_t		*pixel_dest;
	char		*pixel_src;
	uint32_t	src_color;
	int			y;
	int			x;

	if (texoffset < 0)
		return;
	y = 0;
	color <<= 8;
	color |= 0xFF;
	while (y < FONT_HEIGHT)
	{
		pixel_src = &font_atlas.pixels[(y * font_atlas.width + texoffset) * BPP];
		pixel_dest = image->data + ((y * image->width + imgoffset) * BPP);
		x = 0;
		while (x < FONT_WIDTH)
		{
			src_color = *(uint32_t *)(pixel_src + x * BPP);
			if (src_color != 0xFF000000)
				*(uint32_t *)(pixel_dest + x * BPP) = color;
			else
			 	*(uint32_t *)(pixel_dest + x *BPP) = 0x00;
			x++;
		}
		y++;
	}
}

int32_t mlx_get_texoffset(char c)
{
    bool	is_print;

	if (!isascii(c))
		return (0);
	is_print = isprint(c);
    return ((-1 * !is_print + ((FONT_WIDTH + 4) * c) * is_print) + 4);
}

int	mlx_string_put(void *mlx_ptr, void *win_ptr, int x, int y,
				int color, char *string)
{
	t_img		*img;
	size_t		str_size;
	int32_t		img_offset;
	t_window	*window;

	window = (t_window *)win_ptr;
	if (!window)
		return (1);
	str_size = strlen(string);
	img = mlx_new_image(mlx_ptr, FONT_WIDTH * str_size, FONT_HEIGHT);
	if (!img)
		return (1);
	img_offset = 0;
	for (size_t i = 0; i < str_size; i++, img_offset += FONT_WIDTH)
		mlx_draw_char(img, mlx_get_texoffset(string[i]), img_offset, color);
	glfwMakeContextCurrent(window->glfw_window);
	glUseProgram(window->shader_program);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, img->texture_id);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,
		img->width, img->height, GL_RGBA,
		GL_UNSIGNED_BYTE, img->data);
	_set_pos_and_size_of_texture(window, img, x, y);
	glBindVertexArray(window->vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glFlush();
	mlx_destroy_image(mlx_ptr, img);
	return (0);
}
