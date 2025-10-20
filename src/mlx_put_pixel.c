/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:39:24 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/20 14:44:38 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"

static void	_draw_pixel(void *img_ptr, int x, int y, unsigned int color)
{
	int				bits_per_pixel;
	int				line_length;
	void			*addr;
	char			*dst;
	t_img			*img;

	img = (t_img *)img_ptr;
	addr = mlx_get_data_addr(img_ptr, &bits_per_pixel, &line_length, NULL);
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = addr + (y * line_length + x * (bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color)
{
	t_img		*img;
	t_window	*win;

	win = (t_window *)win_ptr;
	img = mlx_new_image(mlx_ptr, win->width, win->height);
	_draw_pixel(img, x, y, color);
	mlx_put_image_to_window(mlx_ptr, win, img, 0, 0);
	mlx_destroy_image(mlx_ptr, img);
	return (0);
}
