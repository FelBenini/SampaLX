/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_string_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 19:56:05 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/28 14:18:28 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_TEXT 4096

static int32_t	mlx_get_texoffset(char c)
{
	bool	is_print;

	if (!isascii(c))
		return (0);
	is_print = isprint(c);
	return ((-1 * !is_print + ((FONT_WIDTH + 4) * c) * is_print) + 4);
}

static void	_init_text(t_window *win)
{
	unsigned int	*indices;
	unsigned int	idx;
	unsigned int	i;

	glfwMakeContextCurrent(win->glfw_window);
	win->text_program = _create_text_program();
	glGenTextures(1, &win->font_texture);
	glBindTexture(GL_TEXTURE_2D, win->font_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, font_atlas.width, font_atlas.height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, font_atlas.pixels);
	glGenVertexArrays(1, &win->text_vao);
	glGenBuffers(1, &win->text_vbo);
	glGenBuffers(1, &win->text_ebo);
	glBindVertexArray(win->text_vao);
	glBindBuffer(GL_ARRAY_BUFFER, win->text_vbo);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
		(void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
		(void *)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	indices = malloc(sizeof(unsigned int) * MAX_TEXT * 6);
	if (!indices)
		return ;
	idx = 0;
	i = 0;
	while (i < MAX_TEXT)
	{
		indices[idx++] = i * 4 + 0;
		indices[idx++] = i * 4 + 1;
		indices[idx++] = i * 4 + 2;
		indices[idx++] = i * 4 + 2;
		indices[idx++] = i * 4 + 3;
		indices[idx++] = i * 4 + 0;
		i++;
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, win->text_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * MAX_TEXT * 6,
		indices, GL_STATIC_DRAW);
	free(indices);
	win->loc_u_window = glGetUniformLocation(win->text_program, "uWindow");
	win->loc_u_color = glGetUniformLocation(win->text_program, "uColor");
	win->loc_u_atlas = glGetUniformLocation(win->text_program, "uAtlas");
	win->text_capacity = 0;
	win->text_initialized = 1;
}

static void	_fill_glyph(float *verts, size_t i, char c, int x, int y)
{
	float		off;
	float		u0;
	float		u1;
	float		x0;
	float		y0;
	float		pos[4][2];
	float		uv[4][2];
	int			k;

	off = (float)mlx_get_texoffset(c);
	u0 = off / (float)font_atlas.width;
	u1 = (off + FONT_WIDTH) / (float)font_atlas.width;
	x0 = x + i * FONT_WIDTH;
	y0 = y;
	pos[0][0] = x0;
	pos[0][1] = y0;
	pos[1][0] = x0 + FONT_WIDTH;
	pos[1][1] = y0;
	pos[2][0] = x0 + FONT_WIDTH;
	pos[2][1] = y0 + FONT_HEIGHT;
	pos[3][0] = x0;
	pos[3][1] = y0 + FONT_HEIGHT;
	uv[0][0] = u0;
	uv[0][1] = 0.0f;
	uv[1][0] = u1;
	uv[1][1] = 0.0f;
	uv[2][0] = u1;
	uv[2][1] = 1.0f;
	uv[3][0] = u0;
	uv[3][1] = 1.0f;
	k = 0;
	while (k < 4)
	{
		verts[(i * 4 + k) * 4 + 0] = pos[k][0];
		verts[(i * 4 + k) * 4 + 1] = pos[k][1];
		verts[(i * 4 + k) * 4 + 2] = uv[k][0];
		verts[(i * 4 + k) * 4 + 3] = uv[k][1];
		k++;
	}
}

int	mlx_string_put(void *mlx_ptr, void *win_ptr, int x, int y,
				int color, char *string)
{
	t_window	*window;
	float		*verts;
	size_t		str_size;
	size_t		i;
	float		r;
	float		g;
	float		b;

	(void)mlx_ptr;
	window = (t_window *)win_ptr;
	if (!window || !window->glfw_window)
		return (1);
	if (!window->text_initialized)
		_init_text(window);
	str_size = strlen(string);
	if (str_size > MAX_TEXT)
		str_size = MAX_TEXT;
	if (str_size == 0)
		return (0);
	verts = malloc(sizeof(float) * 4 * 4 * str_size);
	if (!verts)
		return (1);
	i = 0;
	while (i < str_size)
	{
		_fill_glyph(verts, i, string[i], x, y);
		i++;
	}
	r = ((color >> 16) & 0xFF) / 255.0f;
	g = ((color >> 8) & 0xFF) / 255.0f;
	b = (color & 0xFF) / 255.0f;
	glfwMakeContextCurrent(window->glfw_window);
	glUseProgram(window->text_program);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, window->font_texture);
	glUniform2f(window->loc_u_window, (float)window->width,
		(float)window->height);
	glUniform4f(window->loc_u_color, r, g, b, 1.0f);
	glUniform1i(window->loc_u_atlas, 0);
	glBindVertexArray(window->text_vao);
	glBindBuffer(GL_ARRAY_BUFFER, window->text_vbo);
	if (str_size > window->text_capacity)
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 4 * str_size,
			verts, GL_DYNAMIC_DRAW);
		window->text_capacity = str_size;
	}
	else
		glBufferSubData(GL_ARRAY_BUFFER, 0,
			sizeof(float) * 4 * 4 * str_size, verts);
	glDrawElements(GL_TRIANGLES, (GLsizei)(str_size * 6), GL_UNSIGNED_INT, 0);
	free(verts);
	return (0);
}
