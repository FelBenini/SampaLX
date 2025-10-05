/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 06:46:19 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/05 07:21:21 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"

int	mlx_loop_end(void *mlx_ptr)
{
	t_xvar	*xvar;

	xvar = (t_xvar *)mlx_ptr;
	xvar->end_loop = 1;
	return (1);
}

int	mlx_loop(void *mlx_ptr)
{
	t_win_list		*current_win;
	t_xvar			*xvar;

	xvar = (t_xvar *)mlx_ptr;
	if (!xvar || !xvar->display)
		return (1);
	if (!xvar->win_list)
	{
		glfwTerminate();
		free(xvar);
		return (1);
	}
	while (!xvar->end_loop && xvar->win_list)
	{
		glfwPollEvents();
		current_win = xvar->win_list;
		while (current_win)
		{
			if (xvar->loop_hook)
			{
				if (xvar->loop_hook(xvar->loop_param) != 0)
				{
					xvar->end_loop = 1;
					break;
				}
			}
			else
			{
				glfwMakeContextCurrent(current_win->glfw_win);
				glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);
				glfwSwapBuffers(current_win->glfw_win);
			}

			current_win = current_win->next;
		}
		if (xvar->end_loop)
			break;
		if (!xvar->win_list)
			xvar->end_loop = 1;
	}
	glfwTerminate();
	free(xvar);
	return (0);
}
