/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:25:32 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/14 17:32:59 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"

int	mlx_key_hook(void *win_ptr, int (*funct_ptr)(), void *param)
{
	return (mlx_hook(win_ptr, MLX_KEY_PRESS,
			MLX_KEY_PRESS_MASK, funct_ptr, param));
}
