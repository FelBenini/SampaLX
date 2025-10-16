/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_image_to_window.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 23:21:13 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/16 12:30:06 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"
#include <GLFW/glfw3.h>
#include <stdint.h>
#include <sys/times.h>

// Little Endian on linux fix, pushing the pixels to where they belong
static void _mlx_modify_bits(uint8_t *pixel_start, uint32_t color, t_img *img)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
    // Extract RGBA components
	if (img->endian)
	{
	    r = (color >> 16) & 0xFF;
	    g = (color >> 8) & 0xFF;
	    b = color & 0xFF;
	    a = (color >> 24) & 0xFF;
	}
	else
	{
	    r = (color << 16) & 0xFF;
	    g = (color << 8) & 0xFF;
	    b = color & 0xFF;
	    a = (color << 24) & 0xFF;
	}
	if (color == 0xDDDDDDDD)
		a = 0;
	else
		a = 0xFF;
    *(pixel_start++) = r;
    *(pixel_start++) = g;
    *(pixel_start++) = b;
    *(pixel_start++) = a;
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
			pixelstart = (uint8_t *)(&img->final_texture[(y * img->line_len + x * (img->bits_per_pixel / 8))]);
			_mlx_modify_bits(pixelstart, color, img);
			x++;
		}
		y++;
	}
}

int	mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y)
{
	t_window				*window;
	t_img					*img;

	img = (t_img *)img_ptr;
	window = (t_window *)win_ptr;
	(void)mlx_ptr;
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
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0,
		img->width, img->height, GL_RGBA, GL_UNSIGNED_BYTE, img->final_texture);
	// Draw fullscreen quad
	glBindVertexArray(window->vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glfwSwapBuffers(window->glfw_window);
	glFlush();
	return (0);
}
