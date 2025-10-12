/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 00:47:50 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/12 00:49:59 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"

int	mlx_loop_hook(void *mlx_ptr, void *funct_ptr, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)mlx_ptr;
	if (!mlx)
		return (1);
	mlx->loop_hook = funct_ptr;
	mlx->loop_param = param;
	return (0);
}
