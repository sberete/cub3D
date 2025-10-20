#include "cub3D.h"

// void	mlx_hookes(t_data *fractol)
// {
// 	mlx_key_hook(fractol->win, key_func, fractol);
// 	mlx_hook(fractol->win, DestroyNotify, StructureNotifyMask, hook_func,
// 		fractol);
// 	mlx_mouse_hook(fractol->win, mouse_func, fractol);
// }

// void	fractol_init(t_data *fractol)
// {
// 	fractol->mlx = mlx_init();
// 	fractol->win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, fractol->name);
// 	// fractol->img.img_ptr = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
// 	// fractol->img.pixels_ptr = mlx_get_data_addr(fractol->img.img_ptr,
// 			// &fractol->img.bpp, &fractol->img.line_len, &fractol->img.endian);
// 	// fractol->name = fractol->argv[1];
// 	// fractol->max_iter = 42;
// 	// fractol->zoom = 1.0;
// 	mlx_hookes(fractol);
// }