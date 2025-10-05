/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_destroy_window.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 07:08:57 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/05 07:10:42 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"
#include <GLFW/glfw3.h>

static t_win_list	*get_node_to_destroy(t_xvar *xvar, void *win_ptr)
{
	t_win_list	*node_to_destroy;
	t_win_list	*current;
	t_win_list	*prev;

	prev = NULL;
	node_to_destroy = (t_win_list *)win_ptr;
	current = xvar->win_list;
	while (current && current != node_to_destroy)
	{
		prev = current;
		current = current->next;
	}
	if (!current)
	{
		if (node_to_destroy->glfw_win)
			glfwDestroyWindow(node_to_destroy->glfw_win);
		free(node_to_destroy->title);
		free(node_to_destroy);
		return (NULL);
	}
	if (prev)
		prev->next = current->next;
	else
		xvar->win_list = current->next;
	return (current);
}

int mlx_destroy_window(void *mlx_ptr, void *win_ptr)
{
	t_xvar		*xvar;
	t_win_list	*node_to_free;

	xvar = (t_xvar *)mlx_ptr;
	if (!xvar || !win_ptr)
		return (-1);
	node_to_free = get_node_to_destroy(xvar, win_ptr);
	if (!node_to_free)
		return (-1);
	if (node_to_free->glfw_win)
		glfwDestroyWindow(node_to_free->glfw_win);
	free(node_to_free->title);
	free(node_to_free);
	return (0);
}
