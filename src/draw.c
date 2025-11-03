#include "cub3D.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = img->pixels_ptr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	draw_square(t_img *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			put_pixel(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_map_2d(t_data *cub3d)
{
	char	**map;
	int		tile_size_x;
	int		tile_size_y;
	int		tile_size;
	int		color;

	map = cub3d->map.grid;
	tile_size_x = WIDTH / cub3d->map.width;
	tile_size_y = HEIGHT / cub3d->map.height;
	tile_size = (tile_size_x < tile_size_y) ? tile_size_x : tile_size_y;
	for (int y = 0; map[y]; y++)
	{
		for (int x = 0; map[y][x]; x++)
		{
			color = (map[y][x] == '1') ? 0x00808080 : 0x00FFFFFF;
			for (int i = 0; i < tile_size; i++)
				for (int j = 0; j < tile_size; j++)
					put_pixel(&cub3d->img, x * tile_size + j, y * tile_size + i,
						color);
		}
	}
}

void	draw_player_2d(t_data *cub3d)
{
	int	tile_size_x;
	int	tile_size_y;
	int	tile_size;
	int	px;
	int	py;

	tile_size_x = WIDTH / cub3d->map.width;
	tile_size_y = HEIGHT / cub3d->map.height;
	tile_size = (tile_size_x < tile_size_y) ? tile_size_x : tile_size_y;
	px = (int)(cub3d->player.pos.x * tile_size);
	py = (int)(cub3d->player.pos.y * tile_size);
	for (int dy = -2; dy <= 2; dy++)
	{
		for (int dx = -2; dx <= 2; dx++)
			put_pixel(&cub3d->img, px + dx, py + dy, 0x00FF0000);
	}
}

void	draw_scene(t_data *cub3d)
{
	memset(cub3d->img.pixels_ptr, 0, cub3d->img.line_len * HEIGHT);
	draw_map_2d(cub3d);
	draw_player_2d(cub3d);
	mlx_put_image_to_window(cub3d->mlx.ptr, cub3d->mlx.win, cub3d->img.img_ptr,
		0, 0);
}
