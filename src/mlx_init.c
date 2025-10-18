/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 18:21:20 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/14 16:30:16 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"
#include <GLFW/glfw3.h>

static void	_mlx_glfw_error_callback(int error, const char *description)
{
	fprintf(stderr, "(GLFW Backend): Error %d: %s\n", error, description);
}

void	*mlx_init(void)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	glfwSetErrorCallback(_mlx_glfw_error_callback);
	if (!glfwInit())
	{
		free(mlx);
		return (NULL);
	}
	mlx->is_loop_end = 0;
	mlx->loop_hook = 0;
	mlx->loop_param = 0;
	mlx->win_list = 0;
	return (mlx);
}
