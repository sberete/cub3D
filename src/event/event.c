/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:53:18 by sberete           #+#    #+#             */
/*   Updated: 2025/11/21 16:30:24 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int keycode, t_data *cub3d)
{
	if (keycode == XK_Escape)
		free_all_and_exit(cub3d);
	if (keycode == XK_w)
		cub3d->player.move.forward = 1;
	if (keycode == XK_s)
		cub3d->player.move.backward = 1;
	if (keycode == XK_a)
		cub3d->player.move.left = 1;
	if (keycode == XK_d)
		cub3d->player.move.right = 1;
	if (keycode == XK_Left)
		cub3d->player.move.rotate_left = 1;
	if (keycode == XK_Right)
		cub3d->player.move.rotate_right = 1;
	if (keycode == XK_e)
		interact(cub3d);
	return (0);
}

int	key_release(int keycode, t_data *cub3d)
{
	if (keycode == XK_w)
		cub3d->player.move.forward = 0;
	if (keycode == XK_s)
		cub3d->player.move.backward = 0;
	if (keycode == XK_a)
		cub3d->player.move.left = 0;
	if (keycode == XK_d)
		cub3d->player.move.right = 0;
	if (keycode == XK_Left)
		cub3d->player.move.rotate_left = 0;
	if (keycode == XK_Right)
		cub3d->player.move.rotate_right = 0;
	return (0);
}

int	is_wall(t_data *cub3d, double x, double y)
{
	int		map_x;
	int		map_y;
	char	cell;
	t_door	*door;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= cub3d->map.height || map_x < 0
		|| map_x >= cub3d->map.width)
		return (1);
	cell = cub3d->map.grid[map_y][map_x];
	if (cell == '1')
		return (1);
	if (cell == '2')
	{
		door = find_door(&cub3d->map, map_x, map_y);
		if (door && door->openness < 0.95)
			return (1);
	}
	return (0);
}

static void	move_player(t_data *cub3d, double dir_x, double dir_y, double speed)
{
	double	new_x;
	double	new_y;

	new_x = cub3d->player.pos.x + dir_x * speed;
	new_y = cub3d->player.pos.y + dir_y * speed;
	if (!is_wall(cub3d, new_x, cub3d->player.pos.y))
		cub3d->player.pos.x = new_x;
	if (!is_wall(cub3d, cub3d->player.pos.x, new_y))
		cub3d->player.pos.y = new_y;
}

static void	rotate_player(t_data *cub3d, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub3d->player.dir.x;
	old_plane_x = cub3d->player.plane.x;
	cub3d->player.dir.x = cub3d->player.dir.x * cos(angle) - cub3d->player.dir.y
		* sin(angle);
	cub3d->player.dir.y = old_dir_x * sin(angle) + cub3d->player.dir.y
		* cos(angle);
	cub3d->player.plane.x = cub3d->player.plane.x * cos(angle)
		- cub3d->player.plane.y * sin(angle);
	cub3d->player.plane.y = old_plane_x * sin(angle) + cub3d->player.plane.y
		* cos(angle);
}

void	update_player_position(t_data *cub3d)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.02;
	rot_speed = 0.03;
	if (cub3d->player.move.rotate_left)
		rotate_player(cub3d, -rot_speed);
	if (cub3d->player.move.rotate_right)
		rotate_player(cub3d, rot_speed);
	if (cub3d->player.move.forward)
		move_player(cub3d, cub3d->player.dir.x, cub3d->player.dir.y,
			move_speed);
	if (cub3d->player.move.backward)
		move_player(cub3d, -cub3d->player.dir.x, -cub3d->player.dir.y,
			move_speed);
	if (cub3d->player.move.left)
		move_player(cub3d, cub3d->player.dir.y, -cub3d->player.dir.x,
			move_speed);
	if (cub3d->player.move.right)
		move_player(cub3d, -cub3d->player.dir.y, cub3d->player.dir.x,
			move_speed);
}

int	mouse_move(int x, int y, t_data *cub3d)
{
	int		delta_x;
	double	rot_speed;
	int		center_x;
	int		center_y;

	center_x = WIDTH / 2;
	center_y = HEIGHT / 2;
	(void)y;
	rot_speed = 0.002;
	if (x == center_x)
		return (0);
	delta_x = x - center_x;
	if (delta_x != 0)
		rotate_player(cub3d, delta_x * rot_speed);
	mlx_mouse_move(cub3d->mlx.ptr, cub3d->mlx.win, center_x, center_y);
	return (0);
}

int	render_loop(t_data *cub3d)
{
	update_player_position(cub3d);
	draw_scene(cub3d);
	return (0);
}

void	mlx_hookes(t_data *cub3d)
{
	mlx_hook(cub3d->mlx.win, 2, 1L << 0, key_press, cub3d);
	mlx_hook(cub3d->mlx.win, 3, 1L << 1, key_release, cub3d);
	mlx_hook(cub3d->mlx.win, 17, 0, free_all_and_exit, cub3d);
	mlx_hook(cub3d->mlx.win, MotionNotify, PointerMotionMask, mouse_move,
		cub3d);
	mlx_loop_hook(cub3d->mlx.ptr, render_loop, cub3d);
}
