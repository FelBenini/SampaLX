/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_destroy_window.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:10:31 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/14 13:39:14 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"
#include <GLFW/glfw3.h>

static t_window	*get_window_to_destroy(t_mlx *mlx, t_window *win_to_destroy)
{
	t_window	*current;
	t_window	*prev;

	prev = NULL;
	current = mlx->win_list;
	while (current && current != win_to_destroy)
	{
		prev = current;
		current = current->next;
	}
	if (!current)
	{
		if (win_to_destroy->glfw_window)
			glfwDestroyWindow(win_to_destroy->glfw_window);
		free(win_to_destroy->win_title);
		free(win_to_destroy);
		return (NULL);
	}
	if (prev)
		prev->next = current->next;
	else
		mlx->win_list = current->next;
	return (current);
}

int	mlx_destroy_window(void *mlx_ptr, void *win_ptr)
{
	t_window	*win_to_destroy;
	t_mlx		*mlx;

	mlx = (t_mlx *)mlx_ptr;
	win_to_destroy = get_window_to_destroy(mlx, (t_window *)win_ptr);
	if (!win_to_destroy)
		return (-1);
	if (win_to_destroy->glfw_window)
		glfwDestroyWindow(win_to_destroy->glfw_window);
	free(win_to_destroy->win_title);
	return (0);
}
