/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_destroy_image.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:26:30 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/14 19:46:53 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"

int	mlx_destroy_image(void *mlx_ptr, void *img_ptr)
{
	t_img	*img;

	(void)mlx_ptr;
	img = (t_img *)img_ptr;
	glDeleteTextures(1, &img->texture_id);
	free(img->data);
	free(img->final_texture);
	free(img);
	return (0);
}
