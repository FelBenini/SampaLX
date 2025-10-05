/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_macros.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 17:08:34 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/05 18:51:16 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_INT_MACROS_H
# define MLX_INT_MACROS_H

// --- MiniLibX Events Values ---
#define MLX_KEY_PRESS		2
#define MLX_KEY_RELEASE		3
#define MLX_BUTTON_PRESS	4
#define MLX_BUTTON_RELEASE	5
#define MLX_MOTION_NOTIFY	6
#define MLX_EXPOSE			12
#define MLX_DESTROY_NOTIFY	17
#define MLX_CLIENT_MESSAGE	33
#define MLX_MAX_EVENTS		34

// --- MinilibX Mask Values (X_MASK defines) ---
#define MLX_NO_EVENT_MASK			0L
#define MLX_KEY_PRESS_MASK			(1L<<0)
#define MLX_KEY_RELEASE_MASK		(1L<<1)
#define MLX_BUTTON_PRESS_MASK		(1L<<2)
#define MLX_BUTTON_RELEASE_MASK		(1L<<3)
#define MLX_POINTER_MOTION_MASK		(1L<<6)
#define MLX_EXPOSURE_MASK			(1L<<15)
#define MLX_STRUCTURE_NOTIFY_MASK	(1L<<17)

// --- Functions declarations for loop_hooks ---
typedef int (*t_key_funct)(int keycode, void *param);
typedef int (*t_mouse_funct)(int button, int x, int y, void *param);
typedef int (*t_motion_funct)(int x, int y, void *param);
typedef int (*t_expose_funct)(void *param);
typedef int (*t_destroy_funct)(void *param);

#endif
