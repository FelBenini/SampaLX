/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_dispatchers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:21:10 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/17 18:22:45 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"
#include <GLFW/glfw3.h>

void	_mlx_glfw_dispatch_key_callback(GLFWwindow *window, int key,
								int scancode, int action, int mods)
{
	t_window	*win_data;
	int			mlx_event_code;
	int			mlx_keycode;
	t_key_funct	user_hook;

	win_data = (t_window *)glfwGetWindowUserPointer(window);
	if (!win_data)
		return ;
	mlx_event_code = 0;
	mlx_keycode = _glfw_to_mlx_keycode(key);
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
		mlx_event_code = MLX_KEY_PRESS;
	else if (action == GLFW_RELEASE)
		mlx_event_code = MLX_KEY_RELEASE;
	if (mlx_event_code > 0 && win_data->hooks[mlx_event_code].hook)
	{
		user_hook = (t_key_funct)(void *)win_data->hooks[mlx_event_code].hook;
		user_hook(mlx_keycode, win_data->hooks[mlx_event_code].param);
		glfwPollEvents();
	}
	(void)scancode;
	(void)mods;
}

void	_mlx_glfw_dispatch_mouse_button_callback(GLFWwindow *window, int button,
											int action, int mods)
{
	t_window		*win_data;
	double			xpos;
	double			ypos;
	int				mlx_event_code;
	t_mouse_funct	user_hook;

	win_data = (t_window *)glfwGetWindowUserPointer(window);
	if (!win_data)
		return ;
	glfwGetCursorPos(window, &xpos, &ypos);
	mlx_event_code = 0;
	button = _glfw_mouse_to_mlx(button);
	if (action == GLFW_PRESS)
		mlx_event_code = MLX_BUTTON_PRESS;
	else if (action == GLFW_RELEASE)
		mlx_event_code = MLX_BUTTON_RELEASE;
	if (mlx_event_code > 0 && win_data->hooks[mlx_event_code].hook)
	{
		user_hook = (t_mouse_funct)(void *)win_data->hooks[mlx_event_code].hook;
		user_hook(button, (int)xpos, (int)ypos,
			win_data->hooks[mlx_event_code].param);
		glfwPollEvents();
	}
	(void)mods;
}

void	_mlx_glfw_dispatch_scroll_callback(GLFWwindow *window,
										double xoffset, double yoffset)
{
	t_window		*win_data;
	double			xpos;
	double			ypos;
	t_mouse_funct	user_hook;
	int				mlx_button;

	win_data = (t_window *)glfwGetWindowUserPointer(window);
	if (!win_data)
		return ;
	glfwGetCursorPos(window, &xpos, &ypos);
	mlx_button = 5;
	if (yoffset > 0)
		mlx_button = 4;
	if (win_data->hooks[MLX_BUTTON_PRESS].hook)
	{
		user_hook = (t_mouse_funct)
			(void *)win_data->hooks[MLX_BUTTON_PRESS].hook;
		user_hook(mlx_button, (int)xpos, (int)ypos,
			win_data->hooks[MLX_BUTTON_PRESS].param);
		glfwPollEvents();
	}
	(void)xoffset;
}

void	_mlx_glfw_dispatch_cursor_pos_callback(GLFWwindow *window,
											double xpos, double ypos)
{
	t_window		*win_data;
	t_motion_funct	user_hook;

	win_data = (t_window *)glfwGetWindowUserPointer(window);
	if (!win_data)
		return ;
	if (win_data->hooks[MLX_MOTION_NOTIFY].hook)
	{
		user_hook = (t_motion_funct)
			(void *)win_data->hooks[MLX_MOTION_NOTIFY].hook;
		user_hook((int)xpos, (int)ypos,
			win_data->hooks[MLX_MOTION_NOTIFY].param);
		glfwPollEvents();
	}
}

void	_mlx_glfw_dispatch_framebuffer_size_callback(GLFWwindow *window,
												int width, int height)
{
	t_window		*win_data;
	t_expose_funct	user_hook;

	win_data = (t_window *)glfwGetWindowUserPointer(window);
	if (!win_data)
		return ;
	glViewport(0, 0, width, height);
	win_data->width = width;
	win_data->height = height;
	if (win_data->hooks[MLX_EXPOSE].hook)
	{
		user_hook = (t_expose_funct)(void *)win_data->hooks[MLX_EXPOSE].hook;
		user_hook(win_data->hooks[MLX_EXPOSE].param);
		glfwPollEvents();
	}
}

void	_mlx_glfw_dispatch_window_close_callback(GLFWwindow *window)
{
	t_window		*win_data;
	t_destroy_funct	user_hook;

	win_data = (t_window *)glfwGetWindowUserPointer(window);
	if (!win_data)
		return ;
	if (win_data->hooks[MLX_DESTROY_NOTIFY].hook)
	{
		user_hook = (t_destroy_funct)
			(void *)win_data->hooks[MLX_DESTROY_NOTIFY].hook;
		user_hook(win_data->hooks[MLX_DESTROY_NOTIFY].param);
		glfwPollEvents();
	}
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}
