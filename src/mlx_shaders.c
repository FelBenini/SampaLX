/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_shaders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:36:14 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/13 00:29:48 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"

static const char	*g_vertext_shader_src = "#version 330 core\n"
	"layout(location=0) in vec2 aPos;\n"
	"layout(location=1) in vec2 aTex;\n"
	"out vec2 TexCoord;\n"
	"uniform vec2 uPosition;\n"
	"uniform vec2 uSize;\n"
	"uniform vec2 uWindow;\n"
	"void main() {\n"
	"   vec2 pos = aPos * uSize + uPosition;\n"
	"   vec2 clipPos = vec2(\n"
	"       (pos.x / uWindow.x) * 2.0 - 1.0,\n"
	"       1.0 - (pos.y / uWindow.y) * 2.0\n"
	"   );\n"
	"   TexCoord = aTex;\n"
	"   gl_Position = vec4(clipPos, 0.0, 1.0);\n"
	"}";

static const char	*g_fragment_shader_src = "#version 330 core\n"
	"in vec2 TexCoord;\n"
	"out vec4 FragColor;\n"
	"uniform sampler2D uTexture;\n"
	"void main() {\n"
	"    FragColor = texture(uTexture, TexCoord);\n"
	"}";

static unsigned int	compile_shader(unsigned int type, const char *src)
{
	unsigned int	shader;
	int				success;
	char			info[512];

	shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
		glGetShaderInfoLog(shader, 512, NULL, info);
	return (shader);
}

unsigned int	_create_shader_program(void)
{
	unsigned int	vertex_shader;
	unsigned int	fragment_shader;
	unsigned int	program;
	int				success;
	char			info[512];

	vertex_shader = compile_shader(GL_VERTEX_SHADER, g_vertext_shader_src);
	fragment_shader = compile_shader(GL_FRAGMENT_SHADER, g_fragment_shader_src);
	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, info);
		fprintf(stderr, "Shader linking failed:\n%s\n", info);
	}
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glUseProgram(program);
	glUniform1i(glGetUniformLocation(program, "uTexture"), 0);
	glUseProgram(0);
	return (program);
}
