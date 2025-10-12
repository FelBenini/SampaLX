/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 06:30:56 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/06 01:01:22 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx.h"
#include <stdio.h>

int	loop_hook(int *param)
{
	(*param)++;
	return (0);
}

void	draw_pixel(void *data, int x, int y, unsigned int color)
{
	unsigned char	*dst;
	int				width = 500;
	int				height = 500;
	int				bits_per_pixel;
	int				line_length;
	void			*addr;

	addr = mlx_get_data_addr(data, &bits_per_pixel, &line_length, NULL);
	if (x < 0 || x >= width || y < 0 || y >= height)
		return ;
	dst = addr + (y * line_length + x * (bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(void *data)
{
	int	x;
	int	y;

	x = 100;
	while (x < 400)
	{
		y = 100;
		while (y < 400)
		{
			draw_pixel(data, x, y, 0xFF0000FF);
			y++;
		}
		x++;
	}
}

int main(void)
{
    void *mlx;
	mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "Texture Test");
    void *img = mlx_new_image(mlx, 800, 600);

	draw_square(img);
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_loop(mlx);
    return 0;
}
