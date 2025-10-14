/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:34:05 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/14 14:37:22 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"
#include <GLFW/glfw3.h>

int	mlx_hook(void *win_ptr, int x_event, int x_mask, void *funct, void *param)
{
	t_window	*win;

	win = (t_window *)win_ptr;
	if (!win)
		return (1);
	if (!win->glfw_window)
		return (1);
	if (x_event < 0 || x_event >= MLX_MAX_EVENTS)
		return (1);
	win->hooks[x_event].hook = (int (*)())funct;
	win->hooks[x_event].param = param;
	win->hooks[x_event].mask = x_mask;
	glfwSetWindowUserPointer(win->glfw_window, win);
	if (x_event == MLX_KEY_PRESS)
		glfwSetInputMode(win->glfw_window, GLFW_STICKY_KEYS, GL_TRUE);
	return (0);
}
