/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 12:00:29 by yviavant          #+#    #+#             */
/*   Updated: 2020/10/13 12:00:31 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		s_keypress(int keycode, t_g *g)
{
	if (keycode == FORWARD)
		g->mlx.player.forward = 1;
	else if (keycode == DOWN)
		g->mlx.player.back = 1;
	else if (keycode == ROTATE_LEFT)
		g->mlx.player.r_left = 1;
	else if (keycode == ROTATE_RIGHT)
		g->mlx.player.r_right = 1;
	return (0);
}

int		s_keyrelease(int keycode, t_g *g)
{
	if (keycode == FORWARD)
		g->mlx.player.forward = 0;
	else if (keycode == DOWN)
		g->mlx.player.back = 0;
	else if (keycode == ROTATE_LEFT)
		g->mlx.player.r_left = 0;
	else if (keycode == ROTATE_RIGHT)
		g->mlx.player.r_right = 0;
	else if (keycode == ECHAP)
		s_close(g);
	return (0);
}

void	s_rotate_right(t_g *g)
{
	double	old_dir_x;
	double	old_plane_x;

	if (g->mlx.player.r_right)
	{
		old_dir_x = g->mlx.ray.dir.x;
		g->mlx.ray.dir.x = g->mlx.ray.dir.x * cos(-g->mlx.player.r_speed)
		- g->mlx.ray.dir.y * sin(-g->mlx.player.r_speed);
		g->mlx.ray.dir.y = old_dir_x * sin(-g->mlx.player.r_speed)
		+ g->mlx.ray.dir.y * cos(-g->mlx.player.r_speed);
		old_plane_x = g->mlx.ray.plane.x;
		g->mlx.ray.plane.x = g->mlx.ray.plane.x * cos(-g->mlx.player.r_speed)
		- g->mlx.ray.plane.y * sin(-g->mlx.player.r_speed);
		g->mlx.ray.plane.y = old_plane_x * sin(-g->mlx.player.r_speed)
		+ g->mlx.ray.plane.y * cos(-g->mlx.player.r_speed);
	}
}

void	s_rotate_left(t_g *g)
{
	double	old_dir_x;
	double	old_plane_x;

	if (g->mlx.player.r_left)
	{
		old_dir_x = g->mlx.ray.dir.x;
		g->mlx.ray.dir.x = g->mlx.ray.dir.x * cos(g->mlx.player.r_speed)
		- g->mlx.ray.dir.y * sin(g->mlx.player.r_speed);
		g->mlx.ray.dir.y = old_dir_x * sin(g->mlx.player.r_speed)
		+ g->mlx.ray.dir.y * cos(g->mlx.player.r_speed);
		old_plane_x = g->mlx.ray.plane.x;
		g->mlx.ray.plane.x = g->mlx.ray.plane.x * cos(g->mlx.player.r_speed)
		- g->mlx.ray.plane.y * sin(g->mlx.player.r_speed);
		g->mlx.ray.plane.y = old_plane_x * sin(g->mlx.player.r_speed)
		+ g->mlx.ray.plane.y * cos(g->mlx.player.r_speed);
	}
}

void	s_move(t_g *g)
{
	if (g->mlx.player.forward)
	{
		if (g->parse.map[(int)g->mlx.player.pos.y][(int)(g->mlx.player.pos.x
		+ g->mlx.ray.dir.x * g->mlx.player.speed)] == '0')
			g->mlx.player.pos.x += g->mlx.ray.dir.x * g->mlx.player.speed;
		if (g->parse.map[(int)(g->mlx.player.pos.y + g->mlx.ray.dir.y
		* g->mlx.player.speed)][(int)g->mlx.player.pos.x] == '0')
			g->mlx.player.pos.y += g->mlx.ray.dir.y * g->mlx.player.speed;
	}
	if (g->mlx.player.back)
	{
		if (g->parse.map[(int)g->mlx.player.pos.y][(int)(g->mlx.player.pos.x
		- g->mlx.ray.dir.x * g->mlx.player.speed)] == '0')
			g->mlx.player.pos.x -= g->mlx.ray.dir.x * g->mlx.player.speed;
		if (g->parse.map[(int)(g->mlx.player.pos.y - g->mlx.ray.dir.y
		* g->mlx.player.speed)][(int)g->mlx.player.pos.x] == '0')
			g->mlx.player.pos.y -= g->mlx.ray.dir.y * g->mlx.player.speed;
	}
}
