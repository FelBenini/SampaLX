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

#include "../includes/mlx_int.h"

int render_frame(void *param)
{
    t_xvar *xvar = (t_xvar *)param;
    t_win_list *win = xvar->win_list;

    // Draw your image in the window
	if (win && win->img_list)
		mlx_put_image_to_window(xvar, win, win->img_list, 0, 0);
	printf("aaaaa");
    return 0;
}

int main(void)
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 600, 400, "Loop Hook Example");
    void *img = mlx_new_image(mlx, 400, 400);

    // Fill image with color
    int bpp, line_len, endian;
    char *addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);
    for (int y = 0; y < 400; y++)
        for (int x = 0; x < 400; x++)
            *(unsigned int *)(addr + y * line_len + x * 4) = 0x00FF00; // green

    ((t_win_list *)win)->img_list = img;

    mlx_loop_hook(mlx, render_frame, mlx);
    mlx_loop(mlx);

    return 0;
}

