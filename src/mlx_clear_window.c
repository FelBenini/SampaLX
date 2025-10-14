/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_clear_window.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:54:28 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/14 16:03:03 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"
#include <GLFW/glfw3.h>

int	mlx_clear_window(void *mlx_ptr, void *win_ptr)
{
	t_window	*win;

	(void)mlx_ptr;
	win = (t_window *)win_ptr;
	glfwMakeContextCurrent(win->glfw_window);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(win->glfw_window);
	return (0);
}
