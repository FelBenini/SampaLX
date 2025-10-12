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

