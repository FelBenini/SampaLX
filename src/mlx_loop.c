/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 06:46:19 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/05 23:03:16 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"

int     mlx_loop_end(void *mlx_ptr)
{
	t_xvar 	*xvar;

	xvar = (t_xvar *)mlx_ptr;
	xvar->end_loop = 1;
	return (1);
}

int     mlx_loop(void *mlx_ptr)
{
	t_win_list	*current_win;
	t_win_list	*temp_win;
	t_xvar		*xvar;

	xvar = (t_xvar *)mlx_ptr;
	if (!xvar || !xvar->display)
		return (1);
	if (!xvar->win_list)
		return (1);
	current_win = xvar->win_list;
	while (current_win)
	{
		glfwSetKeyCallback(current_win->glfw_win, _mlx_glfw_dispatch_key_callback);
		glfwSetMouseButtonCallback(current_win->glfw_win, _mlx_glfw_dispatch_mouse_button_callback);
		glfwSetCursorPosCallback(current_win->glfw_win, _mlx_glfw_dispatch_cursor_pos_callback);
		glfwSetFramebufferSizeCallback(current_win->glfw_win, _mlx_glfw_dispatch_framebuffer_size_callback);
		glfwSetWindowCloseCallback(current_win->glfw_win, _mlx_glfw_dispatch_window_close_callback);
		current_win = current_win->next;
    }
	while (!xvar->end_loop && xvar->win_list)
	{
		glfwPollEvents();
		if (xvar->loop_hook)
		{
			if (xvar->loop_hook(xvar->loop_param) != 0)
				xvar->end_loop = 1;
        }
		current_win = xvar->win_list;
		if (xvar->end_loop)
			break;
		if (!xvar->win_list)
			xvar->end_loop = 1;
	}
	return (0);
}
