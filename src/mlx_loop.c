/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 00:50:13 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/16 14:23:56 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"

int	mlx_loop_end(void *mlx_ptr)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)mlx_ptr;
	mlx->is_loop_end = 1;
	return (0);
}

int	mlx_loop(void *mlx_ptr)
{
	t_mlx		*mlx;
	t_window	*current_window;
	t_key_funct	key_function;

	mlx = (t_mlx *)mlx_ptr;
	if (!mlx || !mlx->win_list)
		return (1);
	// --- Set callbacks for all windows ---
	current_window = mlx->win_list;
	while (current_window)
	{
		if (current_window->hooks[MLX_KEY_PRESS].hook)
		{
			key_function = (t_key_funct)(void *)current_window->hooks[MLX_KEY_PRESS].hook;
			key_function(65293, current_window->hooks[MLX_KEY_PRESS].param);
		}
		glfwSetKeyCallback(current_window->glfw_window, _mlx_glfw_dispatch_key_callback);
		glfwSetMouseButtonCallback(current_window->glfw_window, _mlx_glfw_dispatch_mouse_button_callback);
		glfwSetScrollCallback(current_window->glfw_window, _mlx_glfw_dispatch_scroll_callback);
		glfwSetCursorPosCallback(current_window->glfw_window, _mlx_glfw_dispatch_cursor_pos_callback);
		glfwSetFramebufferSizeCallback(current_window->glfw_window, _mlx_glfw_dispatch_framebuffer_size_callback);
		glfwSetWindowCloseCallback(current_window->glfw_window, _mlx_glfw_dispatch_window_close_callback);
		current_window = current_window->next;
	}
	while (!mlx->is_loop_end && mlx->win_list)
	{
		if (mlx->loop_hook && mlx->loop_hook(mlx->loop_param) != 0)
			mlx->is_loop_end = 1;
		current_window = mlx->win_list;
		while (current_window)
		{
			glfwMakeContextCurrent(current_window->glfw_window);
			current_window = current_window->next;
		}
		if (mlx->is_loop_end)
			break ;
		if (!mlx->win_list)
			mlx->is_loop_end = 1;
		glfwPollEvents();
	}
	return (0);
}

