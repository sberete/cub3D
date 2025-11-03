/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxriimu <sxriimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:26:49 by sberete           #+#    #+#             */
/*   Updated: 2025/11/01 16:03:53 by sxriimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	cub3d->map.texture.north = "textures/simonkraft/wet_sponge.xpm";
	cub3d->map.texture.south = "textures/simonkraft/wet_sponge.xpm";
	cub3d->map.texture.west = "textures/simonkraft/wet_sponge.xpm";
	cub3d->map.texture.east = "textures/simonkraft/wet_sponge.xpm";
	cub3d->map.color.floor = "164,169,20";
	cub3d->map.color.ceiling = "153,204,255";
	if (!cub3d->map.grid)
		return (1);
	found = 0;
	cub3d->map.width = 0;
	cub3d->map.height = 0;
	for (int y = 0; cub3d->map.grid[y]; y++)
	{
		line = cub3d->map.grid[y];
		len = strlen(line);
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
				if (c == 'N') { cub3d->player.dir.x = 0.0;  cub3d->player.dir.y = -1.0; }
				if (c == 'S') { cub3d->player.dir.x = 0.0;  cub3d->player.dir.y =  1.0; }
				if (c == 'E') { cub3d->player.dir.x = 1.0;  cub3d->player.dir.y =  0.0; }
				if (c == 'W') { cub3d->player.dir.x = -1.0; cub3d->player.dir.y =  0.0; }
				found = 1;
			}
		}
	}
	return (0);
}