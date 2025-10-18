/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse_hide.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:24:07 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/14 15:25:26 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"
#include <GLFW/glfw3.h>

int	mlx_mouse_hide(void *mlx_ptr, void *win_ptr)
{
	t_window	*win;

	(void)mlx_ptr;
	win = (t_window *)win_ptr;
	if (!win && !win->glfw_window)
		return (1);
	glfwSetInputMode(win->glfw_window, GLFW_CURSOR,GLFW_CURSOR_HIDDEN);
	return (0);
}
