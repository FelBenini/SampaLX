/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_get_screen_size.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:49:20 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/15 17:49:25 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"

int	mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey)
{
	GLFWmonitor					*monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode *const	vidmode = glfwGetVideoMode(monitor);

	if (!mlx_ptr)
		return (1);
	if (sizex)
		*sizex = vidmode->width;
	if (sizey)
		*sizey = vidmode->height;
	return (0);
}
