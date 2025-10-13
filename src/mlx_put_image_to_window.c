/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_image_to_window.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 23:21:13 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/13 00:40:15 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"
#include <GLFW/glfw3.h>
#include <stdint.h>

// Little Endian on linux fix, pushing the pixels to where they belong
static void	_mlx_modify_bits(uint8_t *pixel_start, uint32_t pixel_color)
{
    *(pixel_start++) = (uint8_t)((pixel_color >> 24) & 0xFF);
    *(pixel_start++) = (uint8_t)((pixel_color >> 16) & 0xFF);
    *(pixel_start++) = (uint8_t)((pixel_color >> 8) & 0xFF);
    *(pixel_start++) = (uint8_t)(pixel_color & 0xFF);
}

// Apply the little endian fix on all the pixels of an image
static void	_mlx_modify_bits_in_img(t_img *img)
{
	uint32_t	color;
	int			y;
	int			x;
	uint8_t		*pixelstart;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			color = *(uint32_t *)(&img->data[(y * img->line_len + x * img->bits_per_pixel / 8)]);
			pixelstart = (uint8_t *)(&img->data[(y * img->line_len + x * (img->bits_per_pixel / 8))]);
			_mlx_modify_bits(pixelstart, color);
			x++;
		}
		y++;
	}
}
int	mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y)
{
	t_window	*window;
	t_img		*img;

	img = (t_img *)img_ptr;
	window = (t_window *)win_ptr;
	(void)mlx_ptr;
	(void)x;
	(void)y;
	if (!window || !img)
		return (1);
	_mlx_modify_bits_in_img(img);
	glfwMakeContextCurrent(window->glfw_window);
	glUseProgram(window->shader_program);

	// Activate texture unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, img->texture_id);

	// Upload texture pixels to GPU
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,
		img->width, img->height, GL_RGBA, GL_UNSIGNED_BYTE, img->data);
	// Draw fullscreen quad
	glBindVertexArray(window->vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glfwSwapBuffers(window->glfw_window);
	glfwPollEvents();
	return (0);
}

