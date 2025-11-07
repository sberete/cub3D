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
	int		y;
	int		x;

	map = cub3d->map.grid;
	tile_size_x = WIDTH / cub3d->map.width;
	tile_size_y = HEIGHT / cub3d->map.height;
	if (tile_size_x < tile_size_y)
		tile_size = tile_size_x;
	else
		tile_size = tile_size_y;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				color = COLOR_WALL;
			else
				color = COLOR_FLOOR;
			draw_square(&cub3d->img, x * tile_size, y * tile_size, color);
			x++;
		}
		y++;
	}
}

void	draw_player_dir_2d(t_data *cub3d)
{
	int		tile_x;
	int		tile_y;
	int		px;
	int		py;
	int		len;
	double	dx;
	double	dy;
	int		i;

	tile_x = WIDTH / cub3d->map.width;
	tile_y = HEIGHT / cub3d->map.height;
	if (tile_x < tile_y)
		len = tile_x;
	else
		len = tile_y;
	len = (int)(len * 0.8);
	px = (int)(cub3d->player.pos.x * tile_x);
	py = (int)(cub3d->player.pos.y * tile_y);
	dx = cub3d->player.dir.x;
	dy = cub3d->player.dir.y;
	i = 0;
	while (i < len)
	{
		put_pixel(&cub3d->img, px + (int)(dx * i), py + (int)(dy * i), GREEN);
		i++;
	}
}

void	draw_player_2d(t_data *cub3d)
{
	int	tile_size_x;
	int	tile_size_y;
	int	tile_size;
	int	px;
	int	py;
	int	dx;
	int	dy;

	tile_size_x = WIDTH / cub3d->map.width;
	tile_size_y = HEIGHT / cub3d->map.height;
	if (tile_size_x < tile_size_y)
		tile_size = tile_size_x;
	else
		tile_size = tile_size_y;
	px = (int)(cub3d->player.pos.x * tile_size);
	py = (int)(cub3d->player.pos.y * tile_size);
	dy = -2;
	while (dy <= 2)
	{
		dx = -2;
		while (dx <= 2)
		{
			put_pixel(&cub3d->img, px + dx, py + dy, RED);
			dx++;
		}
		dy++;
	}
}

void	draw_scene(t_data *cub3d)
{
	memset(cub3d->img.pixels_ptr, 0, cub3d->img.line_len * HEIGHT);
	draw_map_2d(cub3d);
	draw_player_2d(cub3d);
	draw_player_dir_2d(cub3d);
	mlx_put_image_to_window(cub3d->mlx.ptr, cub3d->mlx.win, cub3d->img.img_ptr,
		0, 0);
}
