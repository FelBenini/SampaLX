/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_image_to_window.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 23:40:18 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/06 00:41:26 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"

/*
** mlx_put_image_to_window
**
** Draws the given image onto the specified window using OpenGL.
** Uploads the CPU buffer to the GPU texture, then renders a textured quad
** positioned at (x, y) in window pixel coordinates.
*/
int mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr,
                            int x, int y)
{
    t_xvar     *xvar = (t_xvar *)mlx_ptr;
    t_win_list *win = (t_win_list *)win_ptr;
    t_img      *img = (t_img *)img_ptr;

    (void)xvar; // not directly needed here, but kept for compatibility

    if (!win || !img || !img->data)
        return (1);

    // --- Bind window context ---
    glfwMakeContextCurrent(win->glfw_win);

    // --- Upload CPU pixel data to the GPU texture ---
    glBindTexture(GL_TEXTURE_2D, img->texture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,
                    img->width, img->height,
                    GL_RGBA, GL_UNSIGNED_BYTE, img->data);

    // --- Prepare viewport and transformations ---
    int win_w, win_h;
    glfwGetFramebufferSize(win->glfw_win, &win_w, &win_h);

    // Convert pixel positions to normalized device coordinates (-1 to +1)
    float left   =  (2.0f * x / win_w) - 1.0f;
    float right  =  (2.0f * (x + img->width) / win_w) - 1.0f;
    float top    =  1.0f - (2.0f * y / win_h);
    float bottom =  1.0f - (2.0f * (y + img->height) / win_h);

    // --- Render the image quad ---
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, img->texture);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(left,  bottom);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(right, bottom);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(right, top);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(left,  top);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    // --- Present the frame ---
    glfwSwapBuffers(win->glfw_win);

    return (0);
}

