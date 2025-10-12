/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_new_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 23:02:46 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/13 00:53:27 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"
#include <GLFW/glfw3.h>

void	*mlx_new_image(void *mlx_ptr, int width, int height)
{
	t_img		*img;
	GLFWwindow	*ctx;

	(void)mlx_ptr;
	img = malloc(sizeof(t_img));
	if (!img)
		return NULL;
	img->width = width;
	img->height = height;
	img->endian = 1;
	img->bits_per_pixel = 32;
	img->line_len = width * 4;
	img->data = calloc(width * height * 4, 1);
	if (!img->data)
	{
		free(img);
		return NULL;
	}
	ctx = glfwGetCurrentContext();
	if (!ctx)
		fprintf(stderr, "ERROR: no current GL context when creating texture!\n");
	glGenTextures(1, &img->texture_id);
	glBindTexture(GL_TEXTURE_2D, img->texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
			0, GL_RGBA, GL_UNSIGNED_BYTE, img->data);
	glBindTexture(GL_TEXTURE_2D, 0);
    return (img);
}

