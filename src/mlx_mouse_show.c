/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse_show.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:25:33 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/14 15:25:40 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"
#include <GLFW/glfw3.h>

int	mlx_mouse_show(void *mlx_ptr, void *win_ptr)
{
	t_window	*win;

	win = (t_window *)win_ptr;
	(void)mlx_ptr;
	if (!win && !win->glfw_window)
		return (1);
	glfwSetInputMode(win->glfw_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	return (0);
}
