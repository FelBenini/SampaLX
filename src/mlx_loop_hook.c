#include "../includes/mlx_int.h"

int mlx_loop_hook(void *mlx_ptr, void *f, void *param)
{
    t_xvar	*xvar;

	xvar = (t_xvar *)mlx_ptr;
    if (!xvar)
        return (1);
    xvar->loop_hook = f;
    xvar->loop_param = param;
    return (0);
}

