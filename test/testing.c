#include "../glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>

typedef struct s_img
{
	unsigned int	texture_id;
	int				width;
	int				height;
	unsigned char	*pixels;
}	t_img;

typedef struct s_win
{
	GLFWwindow		*window;
	unsigned int	VAO;
	unsigned int	VBO;
	unsigned int	EBO;
	unsigned int	shader;
	int				width;
	int				height;
}	t_win;

typedef struct s_mlx
{
	int	dummy;
}	t_mlx;

typedef struct s_img_data
{
	unsigned char	*addr;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_length;
}	t_img_data;

const char *vertex_shader_src =
	"#version 330 core\n"
	"layout(location=0) in vec2 aPos;\n"
	"layout(location=1) in vec2 aTex;\n"
	"out vec2 TexCoord;\n"
	"void main(){TexCoord=aTex;gl_Position=vec4(aPos,0.0,1.0);}";

const char *fragment_shader_src =
	"#version 330 core\n"
	"in vec2 TexCoord;\n"
	"out vec4 FragColor;\n"
	"uniform sampler2D uTexture;\n"
	"void main(){FragColor=texture(uTexture,TexCoord);}";

unsigned int	compile_shader(unsigned int type, const char *src)
{
	unsigned int	shader;
	int				success;
	char			info[512];

	shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, info);
	}
	return (shader);
}

unsigned int	create_shader_program(void)
{
	unsigned int	vs;
	unsigned int	fs;
	unsigned int	prog;
	int				success;
	char			info[512];

	vs = compile_shader(GL_VERTEX_SHADER, vertex_shader_src);
	fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_src);
	prog = glCreateProgram();
	glAttachShader(prog, vs);
	glAttachShader(prog, fs);
	glLinkProgram(prog);
	glGetProgramiv(prog, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(prog, 512, NULL, info);
	}
	glDeleteShader(vs);
	glDeleteShader(fs);
	return (prog);
}

void	*mlx_new_window(void *mlx_ptr, int width, int height, char *title)
{
	t_win	*win;
	float	vertices[16] = {-1.f, -1.f, 0.f, 0.f, 1.f, -1.f, 1.f, 0.f, 1.f, 1.f, 1.f, 1.f, -1.f, 1.f, 0.f, 1.f};
	unsigned int	indices[6] = {0, 1, 2, 2, 3, 0};

	(void)mlx_ptr;
	if (!glfwInit())
		return (NULL);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	win = malloc(sizeof(t_win));
	if (!win)
		return (NULL);
	win->width = width;
	win->height = height;
	win->window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!win->window)
	{
		free(win);
		glfwTerminate();
		return (NULL);
	}
	glfwMakeContextCurrent(win->window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		free(win);
		glfwTerminate();
		return (NULL);
	}
	win->shader = create_shader_program();
	glGenVertexArrays(1, &win->VAO);
	glGenBuffers(1, &win->VBO);
	glGenBuffers(1, &win->EBO);
	glBindVertexArray(win->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, win->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, win->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	return (win);
}

void	*mlx_new_image(void *mlx_ptr, int width, int height)
{
	t_img	*img;

	(void)mlx_ptr;
	img = malloc(sizeof(t_img));
	img->width = width;
	img->height = height;
	img->pixels = malloc(width * height * 4);
	for (int i = 0; i < width * height * 4; i++)
		img->pixels[i] = 0;
	glGenTextures(1, &img->texture_id);
	glBindTexture(GL_TEXTURE_2D, img->texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	return (img);
}

void	mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y)
{
	t_win	*win;
	t_img	*img;

	(void)mlx_ptr;
	(void)x;
	(void)y;
	win = (t_win *)win_ptr;
	img = (t_img *)img_ptr;
	if (!win || !img)
		return ;
	glfwMakeContextCurrent(win->window);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, img->texture_id);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, img->width, img->height, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);
	glUseProgram(win->shader);
	glBindVertexArray(win->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glfwSwapBuffers(win->window);
	glfwPollEvents();
}

void	draw_pixel(t_img_data *data, int x, int y, unsigned int color)
{
	unsigned char	*dst;

	if (x < 0 || x >= data->width || y < 0 || y >= data->height)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	dst[0] = (color >> 24) & 0xFF;
	dst[1] = (color >> 16) & 0xFF;
	dst[2] = (color >> 8) & 0xFF;
	dst[3] = color & 0xFF;
}

int	main(void)
{
	t_mlx	mlx;
	void	*win;
	void	*img;
	t_img	*i;
	t_img_data	data;

	win = mlx_new_window(&mlx, 800, 600, "MLX Modern OpenGL");
	img = mlx_new_image(&mlx, 800, 600);
	i = (t_img *)img;
	data.addr = i->pixels;
	data.width = i->width;
	data.height = i->height;
	data.bits_per_pixel = 32;
	data.line_length = i->width * 4;
	draw_pixel(&data, 100, 100, 0xFF0000FF);
	draw_pixel(&data, 200, 200, 0x00FF00FF);
	draw_pixel(&data, 300, 300, 0x0000FFFF);
	while (!glfwWindowShouldClose(((t_win *)win)->window))
		mlx_put_image_to_window(&mlx, win, img, 0, 0);
	free(i->pixels);
	free(i);
	glfwDestroyWindow(((t_win *)win)->window);
	glfwTerminate();
	return (0);
}

