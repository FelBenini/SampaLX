/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 06:30:56 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/14 17:34:17 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx.h"
#include <stdio.h>
#include <stdint.h>

int	mouse_move(int x, int y, void *param)
{
	(void)param;
	printf("%d %d\n", x, y);
	return (0);
}

int	loop_hook(int *param)
{
	(*param)++;
	printf("%d\n", (*param));
	if (*param > 100)
		return (1);
	return (0);
}

void mlx_draw_pixel(uint8_t* pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

void	draw_pixel(void *data, int x, int y, unsigned int color)
{
	int				width = 500;
	int				height = 500;
	int				bits_per_pixel;
	int				line_length;
	void			*addr;
	char			*dst;

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
			draw_pixel(data, x, y, 0xFFFFFF);
			y++;
		}
		x++;
	}
}

int	ft_close_window(void *mlx)
{
	mlx_loop_end(mlx);
	return (0);
}

int	loop_key(int keycode, void *param)
{
	printf("%d\n", keycode);
	(void)param;
	return (0);
}

int main(void)
{
    void *mlx;
	int	x;
	int	y;
	mlx = mlx_init();
    void *win = mlx_new_window(mlx, 1000, 600, "Texture Test");
	mlx_get_screen_size(mlx, &x, &y);
	printf("%d %d\n", x, y);
	mlx_hook(win, 6, 1L << 6, mouse_move, mlx);
	mlx_hook(win, 17, 1L << 0, ft_close_window, mlx);

    void *img = mlx_new_image(mlx, 800, 600);
	void *img2 = mlx_new_image(mlx, 800, 600);

	draw_square(img);
	mlx_key_hook(win, loop_key, mlx);
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	draw_pixel(img2, 200, 200, 0xFF0000);
	mlx_put_image_to_window(mlx, win, img2, 0, 0);
	mlx_put_image_to_window(mlx, win, img2, 0, 0);
	mlx_mouse_hide(mlx, win);
	mlx_mouse_show(mlx, win);
	mlx_loop(mlx);
    return 0;
}
