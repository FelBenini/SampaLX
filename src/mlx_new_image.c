/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_new_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:30:19 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/06 00:34:29 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"

void   *mlx_new_image(void *mlx, int width, int height)
{
    (void)mlx;
    t_img *img = calloc(1, sizeof(t_img));
    if (!img)
        return (NULL);

    img->width = width;
    img->height = height;
    img->bpp = 32;
    img->line_len = width * 4; // 4 bytes per pixel (RGBA)
    img->endian = 0;           // little endian
    img->data = calloc(1, img->line_len * height);
    if (!img->data)
    {
        free(img);
        return (NULL);
    }

    glGenTextures(1, &img->texture);
    glBindTexture(GL_TEXTURE_2D, img->texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, img->data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return img;
}
