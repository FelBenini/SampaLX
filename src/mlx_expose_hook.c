/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_expose_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:07:28 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/16 12:08:30 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"

int	mlx_expose_hook(void *win_ptr, int (*funct_ptr)(), void *param)
{
	return (mlx_hook(win_ptr, MLX_EXPOSE, MLX_EXPOSURE_MASK, funct_ptr, param));
}
