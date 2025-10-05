/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:15:55 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/05 19:53:36 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"
#include <GLFW/glfw3.h>

int	mlx_hook(void *win_ptr, int x_event, int x_mask, void *funct, void *param)
{
	t_win_list	*win;	
	if (!win_ptr)
		return (1);
	win = (t_win_list *)win_ptr;
	if (!win->glfw_win)
		return (1);
	if (x_event < 0 || x_event >= MLX_MAX_EVENTS)
		return (1);
	win->hooks[x_event].hook = (int (*)())funct;
	win->hooks[x_event].param = param;
	win->hooks[x_event].mask = x_mask;
	glfwSetWindowUserPointer(win->glfw_win, win);
	if (x_event == MLX_KEY_PRESS)
		glfwSetInputMode(win->glfw_win, GLFW_STICKY_KEYS, GLFW_TRUE);
	(void)x_mask; // This value stored only for compatibility with og mlx
	return (0);
}
