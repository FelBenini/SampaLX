/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_xpm_file_to_image.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herom-s <heromapp1@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 18:40:00 by herom-s           #+#    #+#             */
/*   Updated: 2026/09/24 18:40:00 by herom-s          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"

typedef struct s_xpm
{
	char			*file;
	char			*cursor;
	int				width;
	int				height;
	int				ncolors;
	int				cpp;
	char			*keys;
	unsigned int	*colors;
	int				*index;
}	t_xpm;

typedef struct s_xpm_name
{
	const char		*name;
	unsigned int	rgb;
}	t_xpm_name;

static const t_xpm_name	*_xpm_name_table(void)
{
	static const t_xpm_name	table[] = {
	{"black", 0x000000}, {"white", 0xFFFFFF}, {"snow", 0xFFFAFA},
	{"gainsboro", 0xDCDCDC}, {"lightgray", 0xD3D3D3}, {"silver", 0xC0C0C0},
	{"darkgray", 0xA9A9A9}, {"dimgray", 0x696969}, {"gray", 0xBEBEBE},
	{"lightslategray", 0x778899}, {"slategray", 0x708090},
	{"darkslategray", 0x2F4F4F}, {"red", 0xFF0000}, {"darkred", 0x8B0000},
	{"indianred", 0xCD5C5C}, {"firebrick", 0xB22222}, {"crimson", 0xDC143C},
	{"salmon", 0xFA8072}, {"tomato", 0xFF6347}, {"coral", 0xFF7F50},
	{"orangered", 0xFF4500}, {"orange", 0xFFA500}, {"darkorange", 0xFF8C00},
	{"gold", 0xFFD700}, {"yellow", 0xFFFF00}, {"khaki", 0xF0E68C},
	{"palegoldenrod", 0xEEE8AA}, {"wheat", 0xF5DEB3}, {"tan", 0xD2B48C},
	{"peru", 0xCD853F}, {"brown", 0xA52A2A}, {"saddlebrown", 0x8B4513},
	{"sienna", 0xA0522D}, {"chocolate", 0xD2691E}, {"lime", 0x00FF00},
	{"green", 0x008000}, {"darkgreen", 0x006400}, {"forestgreen", 0x228B22},
	{"seagreen", 0x2E8B57}, {"limegreen", 0x32CD32},
	{"mediumseagreen", 0x3CB371}, {"springgreen", 0x00FF7F},
	{"palegreen", 0x98FB98}, {"lightgreen", 0x90EE90},
	{"yellowgreen", 0x9ACD32}, {"greenyellow", 0xADFF2F},
	{"olivedrab", 0x6B8E23}, {"olive", 0x808000},
	{"darkolivegreen", 0x556B2F}, {"cyan", 0x00FFFF}, {"aqua", 0x00FFFF},
	{"lightcyan", 0xE0FFFF}, {"paleturquoise", 0xAFEEEE},
	{"turquoise", 0x40E0D0}, {"teal", 0x008080}, {"darkcyan", 0x008B8B},
	{"cadetblue", 0x5F9EA0}, {"steelblue", 0x4682B4}, {"skyblue", 0x87CEEB},
	{"lightskyblue", 0x87CEFA}, {"deepskyblue", 0x00BFFF},
	{"dodgerblue", 0x1E90FF}, {"cornflowerblue", 0x6495ED},
	{"royalblue", 0x4169E1}, {"blue", 0x0000FF}, {"mediumblue", 0x0000CD},
	{"darkblue", 0x00008B}, {"navy", 0x000080}, {"midnightblue", 0x191970},
	{"slateblue", 0x6A5ACD}, {"darkslateblue", 0x483D8B},
	{"mediumslateblue", 0x7B68EE}, {"blueviolet", 0x8A2BE2},
	{"indigo", 0x4B0082}, {"darkorchid", 0x9932CC},
	{"mediumorchid", 0xBA55D3}, {"orchid", 0xDA70D6}, {"violet", 0xEE82EE},
	{"plum", 0xDDA0DD}, {"thistle", 0xD8BFD8}, {"lavender", 0xE6E6FA},
	{"magenta", 0xFF00FF}, {"fuchsia", 0xFF00FF}, {"deeppink", 0xFF1493},
	{"hotpink", 0xFF69B4}, {"pink", 0xFFC0CB}, {"lightpink", 0xFFB6C1},
	{"beige", 0xF5F5DC}, {"ivory", 0xFFFFF0}, {"oldlace", 0xFDF5E6},
	{"linen", 0xFAF0E6}, {"cornsilk", 0xFFF8DC}, {"lightyellow", 0xFFFFE0},
	{"moccasin", 0xFFE4B5}, {"navajowhite", 0xFFDEAD},
	{"peachpuff", 0xFFDAB9}, {"bisque", 0xFFE4C4},
	{"blanchedalmond", 0xFFEBCD}, {"papayawhip", 0xFFEFD5},
	{"maroon", 0x800000}, {"purple", 0x800080},
	{"mediumpurple", 0x9370DB}, {"aquamarine", 0x7FFFD4},
	{"mediumaquamarine", 0x66CDAA}, {NULL, 0}
	};

	return (table);
}

static int	_xpm_hex_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

static int	_xpm_from_hex(char *s, unsigned int *rgb)
{
	int				len;
	int				i;
	int				step;
	unsigned int	v;

	i = 0;
	while (s[i])
	{
		if (_xpm_hex_digit(s[i]) < 0)
			return (0);
		i++;
	}
	len = i;
	if (len != 3 && len != 6 && len != 12)
		return (0);
	step = len / 3;
	v = 0;
	i = 0;
	while (i < 3)
	{
		if (len == 3)
			v = (v << 8) | (_xpm_hex_digit(s[i]) * 16 + _xpm_hex_digit(s[i]));
		else
			v = (v << 8) | ((_xpm_hex_digit(s[i * step]) << 4)
					| _xpm_hex_digit(s[i * step + 1]));
		i++;
	}
	*rgb = v;
	return (1);
}

static void	_xpm_normalize(char *dst, int max, char *src)
{
	int	i;
	int	j;
	int	c;

	i = 0;
	j = 0;
	while (src[i] && j < max - 1)
	{
		c = (unsigned char)src[i++];
		if (c == ' ' || c == '\t' || c == '_')
			continue ;
		if (c >= 'A' && c <= 'Z')
			c += 'a' - 'A';
		dst[j++] = (char)c;
	}
	dst[j] = '\0';
}

static int	_xpm_gray_shade(char *name, unsigned int *rgb)
{
	int	i;
	int	n;
	int	v;

	if (strncmp(name, "gray", 4) == 0 || strncmp(name, "grey", 4) == 0)
		i = 4;
	else
		return (0);
	if (name[i] == '\0')
		return (0);
	n = 0;
	while (name[i] >= '0' && name[i] <= '9')
	{
		n = n * 10 + (name[i] - '0');
		i++;
	}
	if (name[i] != '\0' || n > 100)
		return (0);
	v = (n * 255 + 50) / 100;
	*rgb = ((unsigned int)v << 16) | ((unsigned int)v << 8)
		| (unsigned int)v;
	return (1);
}

static int	_xpm_name_to_rgb(char *name, unsigned int *rgb)
{
	char				norm[64];
	const t_xpm_name	*t;

	_xpm_normalize(norm, (int)sizeof(norm), name);
	if (_xpm_gray_shade(norm, rgb))
		return (1);
	t = _xpm_name_table();
	while (t->name)
	{
		if (strcmp(t->name, norm) == 0)
		{
			*rgb = t->rgb;
			return (1);
		}
		t++;
	}
	return (0);
}

static int	_xpm_parse_color(char *spec, unsigned int *packed)
{
	char			buf[256];
	unsigned int	rgb;
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (spec[i] && j < (int)sizeof(buf) - 1)
		buf[j++] = spec[i++];
	buf[j] = '\0';
	while (j > 0 && (buf[j - 1] == ' ' || buf[j - 1] == '\t'))
		buf[--j] = '\0';
	if (strcmp(buf, "None") == 0)
	{
		*packed = 0x00000000;
		return (1);
	}
	if (buf[0] == '#' && _xpm_from_hex(buf + 1, &rgb))
		*packed = 0xFF000000 | rgb;
	else if (buf[0] != '#' && _xpm_name_to_rgb(buf, &rgb))
		*packed = 0xFF000000 | rgb;
	else
	{
		fprintf(stderr, "[SampaLX] xpm: unknown color '%s', using black\n",
			buf);
		*packed = 0xFF000000;
	}
	return (1);
}

static int	_xpm_next_string(char **cursor, char *dst, int max)
{
	char	*p;
	int		len;

	p = *cursor;
	while (*p && *p != '"')
		p++;
	if (*p != '"')
		return (-1);
	p++;
	len = 0;
	while (*p && *p != '"')
	{
		if (*p == '\\' && (p[1] == '"' || p[1] == '\\'))
		{
			if (len < max - 1)
				dst[len++] = p[1];
			p += 2;
		}
		else
		{
			if (len < max - 1)
				dst[len++] = *p;
			p++;
		}
	}
	if (*p != '"')
		return (-1);
	dst[len] = '\0';
	*cursor = p + 1;
	return (len);
}

static int	_xpm_read_file(char *path, t_xpm *x)
{
	FILE	*f;
	long	size;

	f = fopen(path, "rb");
	if (!f)
		return (0);
	if (fseek(f, 0, SEEK_END) != 0)
		return (fclose(f) == 0);
	size = ftell(f);
	rewind(f);
	if (size <= 0)
		return (fclose(f) == 0);
	x->file = malloc((size_t)size + 1);
	if (!x->file)
		return (fclose(f) == 0);
	if (fread(x->file, 1, (size_t)size, f) != (size_t)size)
	{
		free(x->file);
		x->file = NULL;
		return (fclose(f) == 0);
	}
	x->file[size] = '\0';
	x->cursor = x->file;
	fclose(f);
	return (1);
}

static int	_xpm_read_header(t_xpm *x)
{
	char	hdr[256];
	int		got;

	if (_xpm_next_string(&x->cursor, hdr, (int)sizeof(hdr)) < 0)
		return (0);
	got = sscanf(hdr, "%d %d %d %d", &x->width, &x->height,
			&x->ncolors, &x->cpp);
	if (got != 4 || x->width <= 0 || x->height <= 0 || x->ncolors <= 0
		|| x->cpp < 1 || x->cpp > 8)
		return (0);
	return (1);
}

static int	_xpm_build_index(t_xpm *x)
{
	int	size;
	int	i;
	int	k;

	x->index = NULL;
	if (x->cpp > 2)
		return (1);
	size = 256;
	if (x->cpp == 2)
		size = 65536;
	x->index = malloc(sizeof(int) * (size_t)size);
	if (!x->index)
		return (0);
	i = 0;
	while (i < size)
		x->index[i++] = -1;
	i = 0;
	while (i < x->ncolors)
	{
		if (x->cpp == 1)
			k = (unsigned char)x->keys[i];
		else
			k = (unsigned char)x->keys[(size_t)i * 2]
				| ((unsigned char)x->keys[(size_t)i * 2 + 1] << 8);
		if (x->index[k] == -1)
			x->index[k] = i;
		i++;
	}
	return (1);
}

static int	_xpm_read_palette(t_xpm *x)
{
	char			buf[512];
	int				len;
	int				i;
	int				j;

	x->keys = malloc((size_t)x->ncolors * (size_t)x->cpp);
	x->colors = malloc(sizeof(unsigned int) * (size_t)x->ncolors);
	if (!x->keys || !x->colors)
		return (0);
	i = 0;
	while (i < x->ncolors)
	{
		len = _xpm_next_string(&x->cursor, buf, (int)sizeof(buf));
		if (len < x->cpp + 2)
			return (0);
		memcpy(x->keys + (size_t)i * (size_t)x->cpp, buf, (size_t)x->cpp);
		j = x->cpp;
		while (buf[j] == ' ' || buf[j] == '\t')
			j++;
		if (buf[j] != 'c')
			return (0);
		j++;
		while (buf[j] == ' ' || buf[j] == '\t')
			j++;
		_xpm_parse_color(buf + j, &x->colors[i]);
		i++;
	}
	return (_xpm_build_index(x));
}

static int	_xpm_lookup(t_xpm *x, char *key)
{
	int	k;
	int	i;

	if (x->index)
	{
		if (x->cpp == 1)
			k = (unsigned char)key[0];
		else
			k = (unsigned char)key[0]
				| ((unsigned char)key[1] << 8);
		return (x->index[k]);
	}
	i = 0;
	while (i < x->ncolors)
	{
		if (memcmp(x->keys + (size_t)i * (size_t)x->cpp, key,
				(size_t)x->cpp) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	_xpm_fill(t_xpm *x, t_img *img)
{
	char	*scratch;
	int		y;
	int		i;
	int		idx;
	int		len;

	scratch = malloc((size_t)x->width * (size_t)x->cpp + 8);
	if (!scratch)
		return (0);
	y = 0;
	while (y < x->height)
	{
		len = _xpm_next_string(&x->cursor, scratch,
				x->width * x->cpp + 8);
		if (len < x->width * x->cpp)
		{
			free(scratch);
			return (0);
		}
		i = 0;
		while (i < x->width)
		{
			idx = _xpm_lookup(x, scratch + i * x->cpp);
			if (idx < 0)
				idx = 0;
			*(unsigned int *)(img->data + y * img->line_len + i * 4)
				= x->colors[idx];
			i++;
		}
		y++;
	}
	free(scratch);
	return (1);
}

static void	_xpm_free(t_xpm *x)
{
	free(x->file);
	free(x->keys);
	free(x->colors);
	free(x->index);
}

void	*mlx_xpm_file_to_image(void *mlx_ptr, char *filename,
		int *width, int *height)
{
	t_xpm	x;
	t_img	*img;

	memset(&x, 0, sizeof(x));
	if (!_xpm_read_file(filename, &x) || !_xpm_read_header(&x)
		|| !_xpm_read_palette(&x))
	{
		_xpm_free(&x);
		return (NULL);
	}
	img = (t_img *)mlx_new_image(mlx_ptr, x.width, x.height);
	if (!img)
	{
		_xpm_free(&x);
		return (NULL);
	}
	if (!_xpm_fill(&x, img))
	{
		mlx_destroy_image(mlx_ptr, img);
		_xpm_free(&x);
		return (NULL);
	}
	if (width)
		*width = x.width;
	if (height)
		*height = x.height;
	_xpm_free(&x);
	return (img);
}
