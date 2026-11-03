/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_xpm_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 20:22:45 by fbenini-          #+#    #+#             */
/*   Updated: 2026/11/02 21:21:48 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mlx_int.h"

static const t_xpm_name	*_xpm_name_table(void)
{
	static const t_xpm_name	table[] = {
		{"black", 0x000000},
		{"white", 0xFFFFFF},
		{"snow", 0xFFFAFA},
		{"gainsboro", 0xDCDCDC},
		{"lightgray", 0xD3D3D3},
		{"silver", 0xC0C0C0},
		{"darkgray", 0xA9A9A9},
		{"dimgray", 0x696969},
		{"gray", 0xBEBEBE},
		{"lightslategray", 0x778899},
		{"slategray", 0x708090},
		{"darkslategray", 0x2F4F4F},
		{"red", 0xFF0000},
		{"darkred", 0x8B0000},
		{"indianred", 0xCD5C5C},
		{"firebrick", 0xB22222},
		{"crimson", 0xDC143C},
		{"salmon", 0xFA8072},
		{"tomato", 0xFF6347},
		{"coral", 0xFF7F50},
		{"orangered", 0xFF4500},
		{"orange", 0xFFA500},
		{"darkorange", 0xFF8C00},
		{"gold", 0xFFD700},
		{"yellow", 0xFFFF00},
		{"khaki", 0xF0E68C},
		{"palegoldenrod", 0xEEE8AA},
		{"wheat", 0xF5DEB3},
		{"tan", 0xD2B48C},
		{"peru", 0xCD853F},
		{"brown", 0xA52A2A},
		{"saddlebrown", 0x8B4513},
		{"sienna", 0xA0522D},
		{"chocolate", 0xD2691E},
		{"lime", 0x00FF00},
		{"green", 0x008000},
		{"darkgreen", 0x006400},
		{"forestgreen", 0x228B22},
		{"seagreen", 0x2E8B57},
		{"limegreen", 0x32CD32},
		{"mediumseagreen", 0x3CB371},
		{"springgreen", 0x00FF7F},
		{"palegreen", 0x98FB98},
		{"lightgreen", 0x90EE90},
		{"yellowgreen", 0x9ACD32},
		{"greenyellow", 0xADFF2F},
		{"olivedrab", 0x6B8E23},
		{"olive", 0x808000},
		{"darkolivegreen", 0x556B2F},
		{"cyan", 0x00FFFF},
		{"aqua", 0x00FFFF},
		{"lightcyan", 0xE0FFFF},
		{"paleturquoise", 0xAFEEEE},
		{"turquoise", 0x40E0D0},
		{"teal", 0x008080},
		{"darkcyan", 0x008B8B},
		{"cadetblue", 0x5F9EA0},
		{"steelblue", 0x4682B4},
		{"skyblue", 0x87CEEB},
		{"lightskyblue", 0x87CEFA},
		{"deepskyblue", 0x00BFFF},
		{"dodgerblue", 0x1E90FF},
		{"cornflowerblue", 0x6495ED},
		{"royalblue", 0x4169E1},
		{"blue", 0x0000FF},
		{"mediumblue", 0x0000CD},
		{"darkblue", 0x00008B},
		{"navy", 0x000080},
		{"midnightblue", 0x191970},
		{"slateblue", 0x6A5ACD},
		{"darkslateblue", 0x483D8B},
		{"mediumslateblue", 0x7B68EE},
		{"blueviolet", 0x8A2BE2},
		{"indigo", 0x4B0082},
		{"darkorchid", 0x9932CC},
		{"mediumorchid", 0xBA55D3},
		{"orchid", 0xDA70D6},
		{"violet", 0xEE82EE},
		{"plum", 0xDDA0DD},
		{"thistle", 0xD8BFD8},
		{"lavender", 0xE6E6FA},
		{"magenta", 0xFF00FF},
		{"fuchsia", 0xFF00FF},
		{"deeppink", 0xFF1493},
		{"hotpink", 0xFF69B4},
		{"pink", 0xFFC0CB},
		{"lightpink", 0xFFB6C1},
		{"beige", 0xF5F5DC},
		{"ivory", 0xFFFFF0},
		{"oldlace", 0xFDF5E6},
		{"linen", 0xFAF0E6},
		{"cornsilk", 0xFFF8DC},
		{"lightyellow", 0xFFFFE0},
		{"moccasin", 0xFFE4B5},
		{"navajowhite", 0xFFDEAD},
		{"peachpuff", 0xFFDAB9},
		{"bisque", 0xFFE4C4},
		{"blanchedalmond", 0xFFEBCD},
		{"papayawhip", 0xFFEFD5},
		{"maroon", 0x800000},
		{"purple", 0x800080},
		{"mediumpurple", 0x9370DB},
		{"aquamarine", 0x7FFFD4},
		{"mediumaquamarine", 0x66CDAA},
		{NULL, 0}
	};

	return (table);
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

int	_xpm_name_to_rgb(char *name, unsigned int *rgb)
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
