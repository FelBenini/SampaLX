/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 06:05:56 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/05 07:01:32 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_INT_H
# define MLX_INT_H

# include "../glad/include/glad/glad.h"
# include <GLFW/glfw3.h>
# include <stdlib.h>
# include <stdio.h>
# include "./mlx.h"
# include <string.h>

struct s_win_list;
typedef struct s_win_list t_win_list;

typedef struct _XDisplay Display;
typedef unsigned long Window;
typedef struct _XVisual Visual;
typedef unsigned long Colormap;
typedef unsigned long Atom;

typedef struct s_win_list
{
	GLFWwindow			*glfw_win;
	int					width;
	int					height;
	char				*title;
	void				*img_list;
	int					(*key_hook_func)(int, void *);
	void				*key_hook_param;
	struct s_win_list	*next;
	struct s_xvar		*xvar_ptr;

}	t_win_list;

typedef struct	s_xvar
{
	Display		*display;
	Window		root;
	int			screen;
	int			depth;
	Visual		*visual;
	Colormap	cmap;
	int			private_cmap;
	t_win_list	*win_list;
	int			(*loop_hook)(void *);
	void		*loop_param;
	int			use_xshm;
	int			pshm_format;
	int			do_flush;
	int			decrgb[6];
	Atom		wm_delete_window;
	Atom		wm_protocols;
	int 		end_loop;

	GLFWwindow	*glfw_window;
	int			window_width;
	int			window_height;
	const char	*window_title;
}				t_xvar;

#endif
