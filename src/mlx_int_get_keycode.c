/* ************************************************************************** */
/*                                                                   */
/*                                               :::      ::::::::   */
/*   mlx_int_get_keycode.c                     :+:      :+:    :+:   */
/*                                           +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>          +#+  +:+       +#+        */
/*                                       +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:16:26 by fbenini- #+#    #+#             */
/*   Updated: 2025/10/14 16:16:43 by fbenini-###   ########.fr       */
/*                                                                   */
/* ************************************************************************** */

#include "../includes/mlx_int.h"

int	glfw_to_mlx_keycode(int glfw_keycode)
{
	static const t_keymap	key_mappings[] = {
	// Alphabet keys
		{GLFW_KEY_A, 97},      // 'a'
		{GLFW_KEY_B, 98},      // 'b'
		{GLFW_KEY_C, 99},      // 'c'
		{GLFW_KEY_D, 100},     // 'd'
		{GLFW_KEY_E, 101},     // 'e'
		{GLFW_KEY_F, 102},     // 'f'
		{GLFW_KEY_G, 103},     // 'g'
		{GLFW_KEY_H, 104},     // 'h'
		{GLFW_KEY_I, 105},     // 'i'
		{GLFW_KEY_J, 106},     // 'j'
		{GLFW_KEY_K, 107},     // 'k'
		{GLFW_KEY_L, 108},     // 'l'
		{GLFW_KEY_M, 109},     // 'm'
		{GLFW_KEY_N, 110},     // 'n'
		{GLFW_KEY_O, 111},     // 'o'
		{GLFW_KEY_P, 112},     // 'p'
		{GLFW_KEY_Q, 113},     // 'q'
		{GLFW_KEY_R, 114},     // 'r'
		{GLFW_KEY_S, 115},     // 's'
		{GLFW_KEY_T, 116},     // 't'
		{GLFW_KEY_U, 117},     // 'u'
		{GLFW_KEY_V, 118},     // 'v'
		{GLFW_KEY_W, 119},     // 'w'
		{GLFW_KEY_X, 120},     // 'x'
		{GLFW_KEY_Y, 121},     // 'y'
		{GLFW_KEY_Z, 122},     // 'z'
		// Number keys (1-9, 0)
		{GLFW_KEY_1, 49},      // '1'
		{GLFW_KEY_2, 50},      // '2'
		{GLFW_KEY_3, 51},      // '3'
		{GLFW_KEY_4, 52},      // '4'
		{GLFW_KEY_5, 53},      // '5'
		{GLFW_KEY_6, 54},      // '6'
		{GLFW_KEY_7, 55},      // '7'
		{GLFW_KEY_8, 56},      // '8'
		{GLFW_KEY_9, 57},      // '9'
		{GLFW_KEY_0, 48},      // '0'
		// Function keys (F1-F12)
		{GLFW_KEY_F1, 65470},  // F1
		{GLFW_KEY_F2, 65471},  // F2
		{GLFW_KEY_F3, 65472},  // F3
		{GLFW_KEY_F4, 65473},  // F4
		{GLFW_KEY_F5, 65474},  // F5
		{GLFW_KEY_F6, 65475},  // F6
		{GLFW_KEY_F7, 65476},  // F7
		{GLFW_KEY_F8, 65477},  // F8
		{GLFW_KEY_F9, 65478},  // F9
		{GLFW_KEY_F10, 65479}, // F10
		{GLFW_KEY_F11, 65480}, // F11
		{GLFW_KEY_F12, 65481}, // F12
		// Modifier keys
		{GLFW_KEY_LEFT_SHIFT, 65505},   // Left Shift
		{GLFW_KEY_RIGHT_SHIFT, 65506},  // Right Shift
		{GLFW_KEY_LEFT_CONTROL, 65507}, // Left Control
		{GLFW_KEY_RIGHT_CONTROL, 65508},// Right Control
		{GLFW_KEY_LEFT_ALT, 65513},     // Left Alt
		{GLFW_KEY_RIGHT_ALT, 65514},    // Right Alt
		{GLFW_KEY_LEFT_SUPER, 65515},   // Left Super
		{GLFW_KEY_RIGHT_SUPER, 65516},  // Right Super
		// Arrow keys
		{GLFW_KEY_UP, 65362},    // Up Arrow
		{GLFW_KEY_DOWN, 65364},  // Down Arrow
		{GLFW_KEY_LEFT, 65361},  // Left Arrow
		{GLFW_KEY_RIGHT, 65363}, // Right Arrow
		// Special keys
		{GLFW_KEY_ENTER, 65293},     // Enter
		{GLFW_KEY_ESCAPE, 65307},    // Escape
		{GLFW_KEY_TAB, 65289},       // Tab
		{GLFW_KEY_BACKSPACE, 65288}, // Backspace
		{GLFW_KEY_SPACE, 32},        // Space
		{GLFW_KEY_MINUS, 45},        // Minus
		{GLFW_KEY_EQUAL, 61},        // Equals
		{GLFW_KEY_LEFT_BRACKET, 92}, // Left Bracket
		{GLFW_KEY_RIGHT_BRACKET, 93},// Right Bracket
		{GLFW_KEY_BACKSLASH, 91},    // Backslash
		{GLFW_KEY_SEMICOLON, 59},    // Semicolon
		{GLFW_KEY_COMMA, 44},        // Comma
		{GLFW_KEY_PERIOD, 46},       // Period
		{GLFW_KEY_SLASH, 47},        // Slash
		// Numpad keys
		{GLFW_KEY_KP_0, 65456},        // Numpad 0
		{GLFW_KEY_KP_1, 65457},        // Numpad 1
		{GLFW_KEY_KP_2, 65458},        // Numpad 2
		{GLFW_KEY_KP_3, 65459},        // Numpad 3
		{GLFW_KEY_KP_4, 65460},        // Numpad 4
		{GLFW_KEY_KP_5, 65461},        // Numpad 5
		{GLFW_KEY_KP_6, 65462},        // Numpad 6
		{GLFW_KEY_KP_7, 65463},        // Numpad 7
		{GLFW_KEY_KP_8, 65464},        // Numpad 8
		{GLFW_KEY_KP_9, 65465},        // Numpad 9
		{GLFW_KEY_KP_DECIMAL, 65454},  // Numpad Decimal
		{GLFW_KEY_KP_ADD, 65451},      // Numpad Add
		{GLFW_KEY_KP_SUBTRACT, 65453}, // Numpad Subtract
		{GLFW_KEY_KP_MULTIPLY, 65450}, // Numpad Multiply
		{GLFW_KEY_KP_DIVIDE, 65455},   // Numpad Divide
		// Miscellaneous
		{GLFW_KEY_CAPS_LOCK, 65509},    // Caps Lock
		{GLFW_KEY_SCROLL_LOCK, 65300},  // Scroll Lock
		{GLFW_KEY_NUM_LOCK, 65407},     // Num Lock
		{GLFW_KEY_PRINT_SCREEN, 65377}, // Print Screen
		{GLFW_KEY_PAUSE, 65299},        // Pause
		{GLFW_KEY_INSERT, 65379},       // Insert
		{GLFW_KEY_HOME, 65360},         // Home
		{GLFW_KEY_PAGE_UP, 65365},      // Page Up
		{GLFW_KEY_DELETE, 65535},       // Delete
		{GLFW_KEY_END, 65367},          // End
		{GLFW_KEY_PAGE_DOWN, 65366},    // Page Down
	};
	size_t	num_maps;
	size_t	i;

	num_maps = sizeof(key_mappings) / sizeof(t_keymap);
	i = 0;
	while (i < num_maps)
	{
		if (key_mappings[i].glfw_keycode == glfw_keycode)
			return (key_mappings[i].mlx_keycode);
		i++;
	}
	return (glfw_keycode);
};

