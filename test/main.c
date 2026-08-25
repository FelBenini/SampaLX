/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 06:30:56 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/27 18:16:15 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx.h"
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define CUBE_SIZE 100
#define WIN_WIDTH 1000
#define WIN_HEIGHT 600

typedef struct s_state
{
	void	*mlx;
	void	*win;
	void	*cube;
	int		x;
	int		y;
	int		dx;
	int		dy;
}	t_state;

int	mouse_move(int x, int y, void *param)
{
	(void)param;
	printf("%d %d\n", x, y);
	return (0);
}

int	loop_key(int keycode, void *param)
{
	printf("%d\n", keycode);
	(void)param;
	return (0);
}

int	ft_close_window(void *mlx)
{
	mlx_loop_end(mlx);
	return (0);
}

void	fill_image(void *img, int width, int height, unsigned int color)
{
	char	*addr;
	int		bpp;
	int		line_len;
	int		x;
	int		y;

	addr = mlx_get_data_addr(img, &bpp, &line_len, NULL);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			*(unsigned int *)(addr + y * line_len + x * (bpp / 8)) = color;
			x++;
		}
		y++;
	}
}

int	loop_hook(void *param)
{
	t_state	*s;

	s = (t_state *)param;
	s->x += s->dx;
	s->y += s->dy;
	if (s->x <= 0 || s->x + CUBE_SIZE >= WIN_WIDTH)
		s->dx = -s->dx;
	if (s->y <= 0 || s->y + CUBE_SIZE >= WIN_HEIGHT)
		s->dy = -s->dy;
	mlx_clear_window(s->mlx, s->win);
	for (int i = 0; i <= 20; i++) {
		mlx_string_put(s->mlx, s->win, 370, 20 + (40 * i), 0xFF0000, "Heyyyyy");
	}
	mlx_put_image_to_window(s->mlx, s->win, s->cube, s->x, s->y);
	usleep(8000);
	return (0);
}

int	main(void)
{
	t_state	s;
	int		screen_x;
	int		screen_y;

	s.mlx = mlx_init();
	s.win = mlx_new_window(s.mlx, WIN_WIDTH, WIN_HEIGHT, "Texture Test");
	mlx_get_screen_size(s.mlx, &screen_x, &screen_y);
	printf("%d %d\n", screen_x, screen_y);
	mlx_hook(s.win, 6, 1L << 6, mouse_move, s.mlx);
	mlx_hook(s.win, 17, 1L << 0, ft_close_window, s.mlx);
	mlx_key_hook(s.win, loop_key, s.mlx);
	s.cube = mlx_new_image(s.mlx, CUBE_SIZE, CUBE_SIZE);
	fill_image(s.cube, CUBE_SIZE, CUBE_SIZE, 0xFFFFFF);
	s.x = 100;
	s.y = 100;
	s.dx = 1;
	s.dy = 1;
	mlx_loop_hook(s.mlx, loop_hook, &s);
	mlx_loop(s.mlx);
	return (0);
}
