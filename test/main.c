/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 06:30:56 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/05 07:05:05 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx.h"
#include <sys/time.h>

int	main(void)
{
	void	*mlx;
	void	*win_ptr;
	void	*win2;

	mlx = mlx_init();
	win_ptr = mlx_new_window(mlx, 600, 800, "Heyyy");
	win2 = mlx_new_window(mlx, 600, 810, "HELLLO");
	mlx_loop(mlx);
	(void)win_ptr;
	(void)win2;
	mlx_destroy_window(mlx, win_ptr);
	mlx_destroy_window(mlx, win2);
	return (0);
}
