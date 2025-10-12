/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_new_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 17:51:34 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/13 00:16:24 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"
#include <GLFW/glfw3.h>

void *mlx_new_window(void *mlx_ptr, int width, int height, char *title)
{
	t_window	*win;
	t_mlx		*mlx;
	float		vertices[16] = {
		-1.f, -1.f, 0.f, 0.f,
		1.f, -1.f, 1.f, 0.f,
		1.f, 1.f, 1.f, 1.f,
		-1.f, 1.f, 0.f, 1.f
	};
	unsigned int	indices[6] = {0, 1, 2, 2, 3, 0};


	mlx = (t_mlx *)mlx_ptr;
	win = malloc(sizeof(t_window));
	if (!win || !mlx)
		return (NULL);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	win->width = width;
	win->height = height;
	win->win_title = strdup(title);
	if (!win->win_title)
	{
		free(win);
		return (NULL);
	}
	win->glfw_window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!win->glfw_window)
	{
		free(win->win_title);
		free(win);
		return (NULL);
	}
	glfwMakeContextCurrent(win->glfw_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwDestroyWindow(win->glfw_window);
		free(win->win_title);
		free(win);
		return (NULL);
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	memset(win->hooks, 0, sizeof(win->hooks));
	win->shader_program = _create_shader_program();
	glGenVertexArrays(1, &win->vao);
	glGenBuffers(1, &win->vbo);
	glGenBuffers(1, &win->ebo);
	glBindVertexArray(win->vao);
	glBindBuffer(GL_ARRAY_BUFFER, win->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, win->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT,
		GL_FALSE, 4 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT,
		GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	win->next = mlx->win_list;
	mlx->win_list = win;
	return (win);
}
