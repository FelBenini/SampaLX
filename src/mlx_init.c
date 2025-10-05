/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 06:04:57 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/05 06:18:36 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"

static void	_mlx_glfw_error_callback(int error, const char *description)
{
	fprintf(stderr, "MLX (GLFW backend) Error %d: %s\n", error, description);
}

static void	initialize_dummy_values_fromx11(t_xvar *xvar)
{
	int	i;

	xvar->display = NULL;
	xvar->root = (Window)0;
	xvar->screen = 0;
	xvar->depth = 0;
	xvar->visual = NULL;
	xvar->cmap = (Colormap)0;
	xvar->private_cmap = 0;
	xvar->win_list = NULL;
	xvar->loop_hook = NULL;
	xvar->loop_param = NULL;
	xvar->use_xshm = 0;
	xvar->pshm_format = 0;
	xvar->do_flush = 1;
	i = 0;
	while (i < 6)
	{
		xvar->decrgb[i] = 0;
		i++;
	}
	xvar->wm_delete_window = (Atom)0;
	xvar->wm_protocols = (Atom)0;
	xvar->end_loop = 0;
}

void	*mlx_init(void)
{
	t_xvar	*xvar;

	xvar = (t_xvar *)malloc(sizeof(t_xvar));
	if (!xvar)
		return ((void *)0);
	initialize_dummy_values_fromx11(xvar);
	glfwSetErrorCallback(_mlx_glfw_error_callback);
	if (!glfwInit())
	{
		free(xvar);
		return ((void *)0);
	}
	xvar->display = (Display *)1;
	xvar->glfw_window = NULL;
	xvar->window_width = 0;
	xvar->window_height = 0;
	xvar->window_title = NULL;
	xvar->depth = 24;
	xvar->visual = (Visual *)1;
	xvar->cmap = (Colormap)1;
	return ((void *)xvar);
}
