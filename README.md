# SampaLX

A drop-in reimplementation of [42 school's MiniLibX](https://github.com/42Paris/minilibx-linux), rebuilt on top of **OpenGL 3.3** using **GLFW** and **GLAD** instead of X11.

The public API (`mlx.h`) keeps the original MiniLibX signatures, so existing 42 projects (fract-ol, so_long, cub3d, fdf, ...) can link against `libmlx.a` with little to no source changes — just different link flags.

## About

MiniLibX is historically tied to the X11 window system. SampaLX replaces that backend with a modern GPU-accelerated pipeline:

- **GLFW** handles window creation, context management and input events.
- **GLAD** loads the OpenGL 3.3 core functions at runtime.
- Every image is uploaded as an OpenGL texture and blitted through a small vertex/fragment shader program, so pixels are drawn on the GPU.

## Dependencies

| Dependency | Purpose |
| ---------- | ------- |
| `libglfw3` | Window creation, OpenGL context, input handling |
| `libGL`    | OpenGL implementation |
| `make` + `cc` | Build system and C compiler |
| `emscripten` (optional) | WebGL / WebAssembly builds (`make web`) |

On Debian/Ubuntu-based systems:

```sh
sudo apt install build-essential libglfw3-dev libgl1-mesa-dev
```

## Build

```sh
make          # builds libmlx.a
make clean    # removes object files
make fclean   # removes object files and the library
make re       # fclean + rebuild
```

Link your project with:

```sh
cc your_project.c -L. -lmlx -lglfw -lGL
```

## Quick start

```c
#include "mlx.h"
#include <stdlib.h>

int key_hook(int keycode, void *param)
{
    if (keycode == 65307)   /* Escape */
        mlx_loop_end(param);
    return (0);
}

int main(void)
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "SampaLX");

    mlx_key_hook(win, key_hook, mlx);
    mlx_loop(mlx);
    return (0);
}
```

## Test demo

A small demo program lives in `test/`:

```sh
cd test
make
./program
```

## Web / WebGL build

SampaLX can be compiled to WebAssembly and rendered through **WebGL 2** with Emscripten, so MiniLibX programs run in the browser.

Install Emscripten (on Arch/CachyOS: `sudo pacman -S emscripten`; elsewhere use `emsdk`), then:

```sh
make web                 # builds libmlx_web.a
cd test && make web      # builds program.html (+ program.js, program.wasm)
```

The page must be served over HTTP (`file://` blocks the wasm fetch):

```sh
cd test && python3 -m http.server 8000
# then open http://localhost:8000/program.html
```

Link your own project the same way:

```sh
emcc your_project.c -L. -lmlx_web -sUSE_GLFW=3 -sMIN_WEBGL_VERSION=2 \
  -sMAX_WEBGL_VERSION=2 -sALLOW_MEMORY_GROWTH=1 -o game.html
```

### WebGL notes

- Requires **WebGL 2** (OpenGL ES 3.0); shaders switch to `#version 300 es` automatically.
- Only a single window is supported by the Emscripten GLFW backend.
- `mlx_loop` is driven by `requestAnimationFrame`; after `mlx_loop_end` the last frame stays frozen on the canvas (code after `mlx_loop` does not run on the web).
- Keyboard events require the canvas to have focus (click it once).
- Blocking calls such as `usleep` inside hooks are not supported without `-sASYNCIFY`.
- `mlx_mouse_hide`/`mlx_mouse_show` toggle the CSS cursor; `mlx_get_screen_size` reports the browser screen size.

## Project structure

```
.
├── glad/         # Bundled OpenGL loader (glad.c, glad.h, khrplatform.h)
├── includes/     # Internal headers (mlx_int.h, mlx_int_hooks.h, mlx_font.h)
├── src/          # Library sources (28 files)
├── test/         # Demo program and its Makefile
├── Makefile      # Builds libmlx.a
└── mlx.h         # Public API (also mirrored in includes/)
```

## Feature status

### Implemented

| Function | Description |
| -------- | ----------- |
| `mlx_init` | Initialize the library and GLFW |
| `mlx_new_window` | Create a window (non-resizable, 3.3 core profile) |
| `mlx_clear_window` | Clear the window to black |
| `mlx_pixel_put` | Draw a single pixel to the window |
| `mlx_new_image` | Create an RGBA image buffer |
| `mlx_get_data_addr` | Get the raw pixel buffer and metadata |
| `mlx_put_image_to_window` | Blit an image to the window at (x, y) |
| `mlx_string_put` | Draw a string using the bundled font atlas |
| `mlx_mouse_hook` | Register a mouse-button callback |
| `mlx_key_hook` | Register a key-press callback |
| `mlx_expose_hook` | Register an expose callback |
| `mlx_loop_hook` | Register a per-frame callback |
| `mlx_loop` | Run the event loop |
| `mlx_loop_end` | Stop the event loop |
| `mlx_hook` | Generic hook system for X11-style events/masks |
| `mlx_destroy_window` | Destroy a window |
| `mlx_destroy_image` | Free an image |
| `mlx_destroy_display` | Terminate GLFW and shut down |
| `mlx_mouse_get_pos` | Query the cursor position |
| `mlx_mouse_hide` | Hide the cursor |
| `mlx_mouse_show` | Show the cursor |
| `mlx_get_screen_size` | Query the primary monitor resolution |
| `mlx_xpm_file_to_image` | Load an XPM file into an image (`None`, `#rgb`/`#rrggbb`/`#rrrrggggbbbb`, common X11 color names) |

### Stubs (declared, no-op)

| Function |
| -------- |
| `mlx_do_key_autorepeatoff` |
| `mlx_do_key_autorepeaton` |
| `mlx_do_sync` |
| `mlx_mouse_move` |

### Unimplemented

| Function |
| -------- |
| `mlx_get_color_value` |
| `mlx_set_font` |
| `mlx_xpm_to_image` |

## How it works

- **Windowing** — `mlx_new_window` sets GLFW hints for a 3.3 core context, creates the window, makes it current, and loads GL functions via `gladLoadGLLoader`. Each window owns a `VAO`/`VBO`/`EBO` quad plus a shared shader program.
- **Rendering** — images are kept as CPU-side RGBA buffers (`t_img.data`). `mlx_put_image_to_window` converts each pixel to the proper byte order (handling little-endian hosts), uploads it with `glTexSubImage2D`, and draws the quad. The shader positions/sizes the quad using `uPosition`, `uSize`, and `uWindow` uniforms.
- **Events** — GLFW callbacks are dispatched (`mlx_dispatchers.c`) and mapped back to X11-style event codes and masks (`mlx_int_hooks.h`), so `mlx_hook(win, 2, 1L<<0, ...)` behaves like the original.
- **Keycodes** — a GLFW → X11 keycode table (`mlx_int_get_keycode.c`) keeps the values MiniLibX users expect (e.g. `Escape` = `65307`).
- **Text** — `mlx_string_put` renders glyphs from a bundled bitmap font atlas (`mlx_font.h`) into a texture with a transparent background.
