/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_get_mouse_pos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:47:31 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/14 20:49:36 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"
#include <GLFW/glfw3.h>

int	mlx_mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y)
{
	t_window	*win;
	double		xpos;
	double		ypos;

	(void)mlx_ptr;
	win = (t_window *)win_ptr;
	glfwGetCursorPos(win->glfw_window, &xpos, &ypos);
	if (x)
		*x = (int)xpos;
	if (y)
		*y = (int)ypos;
	return (0);
}
