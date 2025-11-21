/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:52:34 by sberete           #+#    #+#             */
/*   Updated: 2025/11/21 16:30:01 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = img->pixels_ptr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

static void	init_ray(t_data *cub3d, int x, t_ray *ray)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIDTH - 1.0;
	ray->ray_dir_x = cub3d->player.dir.x + cub3d->player.plane.x * camera_x;
	ray->ray_dir_y = cub3d->player.dir.y + cub3d->player.plane.y * camera_x;
	ray->map_x = (int)cub3d->player.pos.x;
	ray->map_y = (int)cub3d->player.pos.y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

static void	init_step(t_data *cub3d, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cub3d->player.pos.x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cub3d->player.pos.x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cub3d->player.pos.y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cub3d->player.pos.y)
			* ray->delta_dist_y;
	}
}

t_door	*find_door(t_map *map, int x, int y)
{
	int	i;

	i = 0;
	while (i < map->door_count)
	{
		if (map->doors[i].x == x && map->doors[i].y == y)
			return (&map->doors[i]);
		i++;
	}
	return (NULL);
}

void	update_doors(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->door_count)
	{
		if (map->doors[i].opening != 0)
		{
			map->doors[i].openness += map->doors[i].opening * 0.05;
			if (map->doors[i].openness >= 1.0)
			{
				map->doors[i].openness = 1.0;
				map->doors[i].opening = 0;
			}
			if (map->doors[i].openness <= 0.0)
			{
				map->doors[i].openness = 0.0;
				map->doors[i].opening = 0;
			}
		}
		i++;
	}
}

void	interact(t_data *cub3d)
{
	int		x;
	int		y;
	t_door	*door;

	x = (int)(cub3d->player.pos.x + cub3d->player.dir.x);
	y = (int)(cub3d->player.pos.y + cub3d->player.dir.y);
	door = find_door(&cub3d->map, x, y);
	if (door)
	{
		if (door->openness < 1.0)
			door->opening = 1;
		else
			door->opening = -1;
	}
}

static void	perform_dda(t_data *cub3d, t_ray *ray)
{
	int		hit;
	t_door	*door;
	char	cell;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		cell = cub3d->map.grid[ray->map_y][ray->map_x];
		if (cell == '1')
			hit = 1;
		else if (cell == '2')
		{
			door = find_door(&cub3d->map, ray->map_x, ray->map_y);
			if (door && door->openness >= 1.0)
				continue ;
			hit = 1;
		}
	}
}

static t_img	*get_texture(t_data *cub3d, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&cub3d->map.texture.west);
		else
			return (&cub3d->map.texture.east);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (&cub3d->map.texture.north);
		else
			return (&cub3d->map.texture.south);
	}
}

static double	compute_perp_dist(t_data *cub3d, t_ray *ray)
{
	if (ray->side == 0)
		return ((ray->map_x - cub3d->player.pos.x + (1 - ray->step_x) / 2)
			/ ray->ray_dir_x);
	return ((ray->map_y - cub3d->player.pos.y + (1 - ray->step_y) / 2)
		/ ray->ray_dir_y);
}

static double	compute_wall_x(t_data *cub3d, t_ray *ray, double perp_dist)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = cub3d->player.pos.y + perp_dist * ray->ray_dir_y;
	else
		wall_x = cub3d->player.pos.x + perp_dist * ray->ray_dir_x;
	return (wall_x - floor(wall_x));
}

static void	compute_draw_limits(double dist, int *line_h, int *start, int *end)
{
	*line_h = (int)(HEIGHT / dist);
	*start = -(*line_h) / 2 + HEIGHT / 2;
	if (*start < 0)
		*start = 0;
	*end = *line_h / 2 + HEIGHT / 2;
	if (*end >= HEIGHT)
		*end = HEIGHT - 1;
}

static void	draw_tex_stripe(t_data *cub3d, t_texinfo t, t_col c)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	step = 1.0 * t.tex->height / c.line_h;
	tex_pos = (c.start - HEIGHT / 2 + c.line_h / 2) * step;
	y = c.start;
	while (y <= c.end)
	{
		tex_y = (int)tex_pos & (t.tex->height - 1);
		tex_pos += step;
		color = *(int *)(t.tex->pixels_ptr + tex_y * t.tex->line_len + t.tex_x
				* (t.tex->bpp / 8));
		put_pixel(&cub3d->img, c.x, y, color);
		y++;
	}
}

void	draw_column(t_data *cub3d, t_ray *ray, int x)
{
	double		perp;
	double		wall_x;
	int			line_h;
	t_col		c;
	t_texinfo	t;

	perp = compute_perp_dist(cub3d, ray);
	if (perp < 0.0001)
		perp = 0.0001;
	compute_draw_limits(perp, &line_h, &c.start, &c.end);
	c.x = x;
	c.line_h = line_h;
	t.tex = get_texture(cub3d, ray);
	wall_x = compute_wall_x(cub3d, ray, perp);
	t.tex_x = (int)(wall_x * t.tex->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		t.tex_x = t.tex->width - t.tex_x - 1;
	draw_tex_stripe(cub3d, t, c);
}

void	draw_scene_3d(t_data *cub3d)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(cub3d, x, &cub3d->ray);
		init_step(cub3d, &cub3d->ray);
		perform_dda(cub3d, &cub3d->ray);
		draw_column(cub3d, &cub3d->ray, x);
		x++;
	}
}

static void	draw_floor_ceiling(t_data *cub3d)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel(&cub3d->img, x, y, cub3d->map.color.ceiling_rgb);
			else
				put_pixel(&cub3d->img, x, y, cub3d->map.color.floor_rgb);
			x++;
		}
		y++;
	}
}

void	draw_scene(t_data *cub3d)
{
	memset(cub3d->img.pixels_ptr, 0, cub3d->img.line_len * HEIGHT);
	draw_floor_ceiling(cub3d);
	update_doors(&cub3d->map);
	draw_scene_3d(cub3d);
	draw_minimap(cub3d);
	mlx_put_image_to_window(cub3d->mlx.ptr, cub3d->mlx.win, cub3d->img.img_ptr,
		0, 0);
}
