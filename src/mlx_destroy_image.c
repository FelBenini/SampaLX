/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_destroy_image.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:26:30 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/14 13:27:47 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"

int	mlx_destroy_image(void *mlx_ptr, void *img_ptr)
{
	t_img	*img;

	(void)mlx_ptr;
	img = (t_img *)img_ptr;
	free(img->data);
	free(img);
	return (0);
}
