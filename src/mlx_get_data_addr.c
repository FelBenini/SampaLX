/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_get_data_addr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 23:17:35 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/12 23:19:22 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"

char	*mlx_get_data_addr(void *img_ptr, int *bpp, int *line_len, int *endian)
{
	t_img	*img;

	img = (t_img *)img_ptr;
	if (!img)
		return (NULL);
	if (bpp)
		*bpp = img->bits_per_pixel;
	if (line_len)
		*line_len = img->line_len;
	if (endian)
		*endian = img->endian;
	return ((char *)img->data);
}
