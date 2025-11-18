/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:52:34 by sberete           #+#    #+#             */
/*   Updated: 2025/11/18 13:52:35 by sberete          ###   ########.fr       */
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

static void	perform_dda(t_data *cub3d, t_ray *ray)
{
	int	hit;

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
		if (cub3d->map.grid[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

static void	draw_column(t_data *cub3d, t_ray *ray, int x)
{
	double	perp_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;

	if (ray->side == 0)
		perp_dist = (ray->map_x - cub3d->player.pos.x + (1 - ray->step_x) / 2)
			/ ray->ray_dir_x;
	else
		perp_dist = (ray->map_y - cub3d->player.pos.y + (1 - ray->step_y) / 2)
			/ ray->ray_dir_y;
	if (perp_dist < 0.0001)
		perp_dist = 0.0001;
	line_height = (int)(HEIGHT / perp_dist);
	draw_start = -line_height / 2 + HEIGHT / 2;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	if (ray->side == 1)
		color = 0x00707070;
	else
		color = 0x00AAAAAA;
	while (draw_start <= draw_end)
	{
		put_pixel(&cub3d->img, x, draw_start, color);
		draw_start++;
	}
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

void	draw_scene(t_data *cub3d)
{
	memset(cub3d->img.pixels_ptr, 0, cub3d->img.line_len * HEIGHT);
	draw_scene_3d(cub3d);
	draw_minimap(cub3d);
	mlx_put_image_to_window(cub3d->mlx.ptr, cub3d->mlx.win, cub3d->img.img_ptr,
		0, 0);
}
