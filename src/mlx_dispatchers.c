/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_dispatchers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 21:14:07 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/05 21:14:52 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"

void	_mlx_glfw_dispatch_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	t_win_list	*win_data;
	int			mlx_event_code;
	int			mlx_keycode;
	t_key_funct	user_hook;

	win_data = (t_win_list *)glfwGetWindowUserPointer(window);
	if (!win_data)
		return;
	mlx_event_code = 0;
	mlx_keycode = key;
	if (key == GLFW_KEY_ESCAPE)
		mlx_keycode = 53;
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
		mlx_event_code = MLX_KEY_PRESS;
	else if (action == GLFW_RELEASE)
		mlx_event_code = MLX_KEY_RELEASE;
	if (mlx_event_code > 0 && win_data->hooks[mlx_event_code].hook)
	{
		user_hook = (t_key_funct)(void *)win_data->hooks[mlx_event_code].hook;
		user_hook(mlx_keycode, win_data->hooks[mlx_event_code].param);
	}
	(void)scancode;
	(void)mods;
}

void	_mlx_glfw_dispatch_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	t_win_list		*win_data;
	double			xpos;
	double			ypos;
	int				mlx_event_code;
	int				mlx_button;
	t_mouse_funct	user_hook;

	win_data = (t_win_list *)glfwGetWindowUserPointer(window);
	if (!win_data)
		return;
    glfwGetCursorPos(window, &xpos, &ypos);
	mlx_event_code = 0;
	mlx_button = button + 1;
	if (action == GLFW_PRESS)
		mlx_event_code = MLX_BUTTON_PRESS;
	else if (action == GLFW_RELEASE)
		mlx_event_code = MLX_BUTTON_RELEASE;
    if (mlx_event_code > 0 && win_data->hooks[mlx_event_code].hook)
    {
        user_hook = (t_mouse_funct)(void *)win_data->hooks[mlx_event_code].hook;
        user_hook(mlx_button, (int)xpos, (int)ypos, win_data->hooks[mlx_event_code].param);
    }
    (void)mods;
}

void	_mlx_glfw_dispatch_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    t_win_list		*win_data;
	t_motion_funct	user_hook;

	win_data = (t_win_list *)glfwGetWindowUserPointer(window);
	if (!win_data)
		return;
	if (win_data->hooks[MLX_MOTION_NOTIFY].hook)
	{
		user_hook = (t_motion_funct)(void *)win_data->hooks[MLX_MOTION_NOTIFY].hook;
		user_hook((int)xpos, (int)ypos, win_data->hooks[MLX_MOTION_NOTIFY].param);
    }
}

void	_mlx_glfw_dispatch_framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	t_win_list		*win_data;
	t_expose_funct	user_hook;

	win_data = (t_win_list *)glfwGetWindowUserPointer(window);	
	if (!win_data)
		return;
	glViewport(0, 0, width, height);
	win_data->width = width;
	win_data->height = height;
	if (win_data->hooks[MLX_EXPOSE].hook)
	{
		user_hook = (t_expose_funct)(void *)win_data->hooks[MLX_EXPOSE].hook;
		user_hook(win_data->hooks[MLX_EXPOSE].param);
	}
}

void	_mlx_glfw_dispatch_window_close_callback(GLFWwindow* window)
{
	t_win_list		*win_data;
	t_destroy_funct	user_hook;

	win_data = (t_win_list *)glfwGetWindowUserPointer(window);
	if (!win_data)
		return;
	if (win_data->hooks[MLX_DESTROY_NOTIFY].hook)
	{
		user_hook = (t_destroy_funct)(void *)win_data->hooks[MLX_DESTROY_NOTIFY].param;
		user_hook(win_data->hooks[MLX_DESTROY_NOTIFY].param);
	}
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

