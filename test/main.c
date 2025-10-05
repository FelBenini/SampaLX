/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 06:30:56 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/05 19:59:10 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx.h"
#include <sys/time.h>
#include <stdio.h>

int	keypress_loop(int keycode, void *param)
{
	printf("%d\n", keycode);
	if (keycode == 53 || keycode == 65307)
		mlx_loop_end(param);
	return (1);
}

int	mouse_move(int x, int y, void *param)
{
	(void)param;
	printf("%d %d\n", x, y);
	return (0);
}

int	main(void)
{
	void	*mlx;
	void	*win_ptr;
	void	*win2;

	mlx = mlx_init();
	win_ptr = mlx_new_window(mlx, 600, 800, "Heyyy");
	win2 = mlx_new_window(mlx, 600, 810, "HELLLO");
	mlx_hook(win_ptr, 2, 1L << 0, keypress_loop, mlx);
	mlx_hook(win_ptr, 6, 1L << 6, mouse_move, mlx);
	mlx_loop(mlx);
	(void)win_ptr;
	(void)win2;
	mlx_destroy_window(mlx, win_ptr);
	mlx_destroy_window(mlx, win2);
	return (0);
}
