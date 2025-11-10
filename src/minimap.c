#include "cub3D.h"

#define MINIMAP_SCALE 0.2
#define MINIMAP_OFFSET_X 10
#define MINIMAP_OFFSET_Y 10

void	draw_tile_minimap(t_data *cub3d, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(&cub3d->img, MINIMAP_OFFSET_X + x + j, MINIMAP_OFFSET_Y
				+ y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_player_minimap(t_data *cub3d)
{
	int	size;
	int	px;
	int	py;
	int	player_size;

	size = (int)((WIDTH * MINIMAP_SCALE) / cub3d->map.width);
	player_size = size / 2;
	px = (int)(cub3d->player.pos.x * size) - player_size / 2;
	py = (int)(cub3d->player.pos.y * size) - player_size / 2;
	draw_tile_minimap(cub3d, px, py, player_size, RED);
}

void	draw_minimap(t_data *cub3d)
{
	char	**map;
	int		size;
	int		y;
	int		x;

	map = cub3d->map.grid;
	size = (int)((WIDTH * MINIMAP_SCALE) / cub3d->map.width);
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_tile_minimap(cub3d, x * size, y * size, size, COLOR_WALL);
			else
				draw_tile_minimap(cub3d, x * size, y * size, size, COLOR_FLOOR);
			x++;
		}
		y++;
	}
	draw_player_minimap(cub3d);
}
