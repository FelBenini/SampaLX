/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_new_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 06:26:02 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/05 07:19:59 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"

static void	_mlx_glfw_error_callback(int error, const char *description)
{
	fprintf(stderr, "MLX (GLFW backend) Error %d: %s\n", error, description);
}

static void	initialize_hints()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwSetErrorCallback(_mlx_glfw_error_callback);
}

void	*mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title)
{
	t_win_list	*new_win_node;
	GLFWwindow	*new_glfw_window;
	t_xvar		*xvar;

	xvar = (t_xvar *)mlx_ptr;
	if (!xvar || !xvar->display)
		return (NULL);
	new_win_node = (t_win_list *)malloc(sizeof(t_win_list));
	if (!new_win_node)
		return (NULL);
	initialize_hints();
	new_glfw_window = glfwCreateWindow(size_x, size_y, title, NULL, NULL);
	if (!new_glfw_window)
	{
		free(new_win_node);
		return (NULL);
	}
	new_win_node->glfw_win = new_glfw_window;
	new_win_node->width = size_x;
	new_win_node->height = size_y;
	new_win_node->title = strdup(title);
	if (!new_win_node->title)
	{
		glfwDestroyWindow(new_glfw_window);
		free(new_win_node);
		return (NULL);
	}
	new_win_node->img_list = NULL;
	new_win_node->key_hook_func = NULL;
	new_win_node->key_hook_param = NULL;
	new_win_node->next = NULL;
	new_win_node->xvar_ptr = xvar;
	glfwMakeContextCurrent(new_glfw_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwDestroyWindow(new_glfw_window);
		free(new_win_node->title);
		free(new_win_node);
		return (NULL);
	}
	glViewport(0, 0, size_x, size_y);
	new_win_node->next = xvar->win_list;
	xvar->win_list = new_win_node;
	return ((void *)new_win_node);
}
