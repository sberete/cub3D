#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_data	cub3D;

	(void)argc;
	(void)argv;
	ft_bzero(&cub3D, sizeof(t_data));
	cub3D.mlx = mlx_init();
	if (!cub3D.mlx)
		mlx_failure(&cub3D, "Mlx Failure");
	cub3D.win = mlx_new_window(cub3D.mlx, WIDTH, HEIGHT, cub3D.name);
	if (!cub3D.mlx)
		mlx_failure(&cub3D, "Win Failure");
	mlx_hookes(&cub3D);
	mlx_loop(cub3D.mlx);
}
