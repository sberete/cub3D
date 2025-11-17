/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxriimu <sxriimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:26:49 by sberete           #+#    #+#             */
/*   Updated: 2025/11/15 01:57:44 by sxriimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
Du coup la je t'ai mis ce que j'aurais besoin que tu me remplisse
Ca sera tout les structures en bas dans le commentaire

typedef struct s_texture
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
}				t_texture;

typedef struct s_color
{
	char		*floor;
	char		*ceiling;
}				t_color;

typedef struct s_map
{
	char		*name;
	t_texture	texture;
	t_color		color;
	char		**grid;
	int			width;
	int			height;
}				t_map;

typedef struct s_direction
{
	double		x;
	double		y;
}				t_direction;

typedef struct s_position
{
	double		x;
	double		y;
}				t_position;

typedef struct s_player
{
	t_direction	dir;
	t_position	pos;
}				t_player;
*/
static char	**fill_test_map(void)
{
	static char	*template[] = {"111111111111111111111", "101000001000000000001",
			"101010101011111110001", "100010100010000010001",
			"111110101111101011101", "100000101000101000001",
			"101111101011101111111", "101000001010100000101",
			"101011111010111110101", "101010001010100010101",
			"101110101010101010101", "100000101010001010001",
			"111111101011111011101", "100000101000100010001",
			"101110101110101110111", "101000100000100010101",
			"101011111111111010101", "100010000000000010001",
			"101010111011111111101", "1N1000001000000000001",
			"111111111111111111111", NULL};

	return (ft_tabdup(template));
}

static void	init_player_plane(t_player *player)
{
	double	fov_factor;

	fov_factor = 0.66;
	if (player->dir.x == 0 && player->dir.y == -1)
	{
		player->plane.x = fov_factor;
		player->plane.y = 0.0;
	}
	else if (player->dir.x == 0 && player->dir.y == 1)
	{
		player->plane.x = -fov_factor;
		player->plane.y = 0.0;
	}
	else if (player->dir.x == 1 && player->dir.y == 0)
	{
		player->plane.x = 0.0;
		player->plane.y = fov_factor;
	}
	else if (player->dir.x == -1 && player->dir.y == 0)
	{
		player->plane.x = 0.0;
		player->plane.y = -fov_factor;
	}
}

int	load_texture(void *mlx_ptr, char *path, t_img *tex)
{
	tex->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &tex->width,
			&tex->height);
	if (!tex->img_ptr)
		return (1);
	tex->pixels_ptr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->pixels_ptr)
		return (1);
	return (0);
}

int	load_all_textures(t_data *cub3d)
{
	if (load_texture(cub3d->mlx.ptr, "./textures/north.xpm",
			&cub3d->map.texture.north))
		return (1);
	if (load_texture(cub3d->mlx.ptr, "./textures/south.xpm",
			&cub3d->map.texture.south))
		return (1);
	if (load_texture(cub3d->mlx.ptr, "./textures/west.xpm",
			&cub3d->map.texture.west))
		return (1);
	if (load_texture(cub3d->mlx.ptr, "./textures/east.xpm",
			&cub3d->map.texture.east))
		return (1);
	return (0);
}

int	parsing(t_data *cub3d, int argc, char **argv)
{
	int		found;
	char	*line;
	size_t	len;
	char	c;

	if (argc != 2)
		return (1);
	cub3d->map.name = argv[1];
	cub3d->map.grid = fill_test_map();
	if (!cub3d->map.grid)
		return (1);
	cub3d->map.color.floor = "164,169,20";
	cub3d->map.color.ceiling = "153,204,255";
	// if (load_all_textures(cub3d))
	// {
	// 	ft_putstr_fd("Erreur : impossible de charger les textures.\n", 2);
	// 	return (1);
	// }
	cub3d->map.width = 0;
	cub3d->map.height = 0;
	found = 0;
	for (int y = 0; cub3d->map.grid[y]; y++)
	{
		line = cub3d->map.grid[y];
		len = ft_strlen(line);
		if ((int)len > cub3d->map.width)
			cub3d->map.width = (int)len;
		cub3d->map.height++;
		for (size_t x = 0; x < len && !found; x++)
		{
			c = line[x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				cub3d->player.pos.x = (double)x + 0.5;
				cub3d->player.pos.y = (double)y + 0.5;
				cub3d->map.grid[y][x] = '0';
				if (c == 'N')
				{
					cub3d->player.dir.x = 0.0;
					cub3d->player.dir.y = -1.0;
				}
				else if (c == 'S')
				{
					cub3d->player.dir.x = 0.0;
					cub3d->player.dir.y = 1.0;
				}
				else if (c == 'E')
				{
					cub3d->player.dir.x = 1.0;
					cub3d->player.dir.y = 0.0;
				}
				else if (c == 'W')
				{
					cub3d->player.dir.x = -1.0;
					cub3d->player.dir.y = 0.0;
				}
				init_player_plane(&cub3d->player);
				found = 1;
			}
		}
	}
	return (0);
}
