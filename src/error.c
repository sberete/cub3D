#include "cub3D.h"

void	mlx_failure(t_data *cub3D, char *str)
{
	printf("%s\n", str);
    close_mlx(cub3D);
}

// void	img_failure(void)
// {
// 	printf("Failure mlx\n");
// 	exit(1);
// }

// void	win_failure(void)
// {
// 	printf("Failure mlx\n");
// 	exit(1);
// }