/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_raycast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 12:08:04 by yviavant          #+#    #+#             */
/*   Updated: 2020/10/13 12:08:10 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	s_init(t_g *g, int i)
{
	g->mlx.ray.camera = 2 * i / (double)g->parse.size.w - 1;
	g->mlx.ray.ray_dir.x = g->mlx.ray.dir.x + g->mlx.ray.plane.x
	* g->mlx.ray.camera;
	g->mlx.ray.ray_dir.y = g->mlx.ray.dir.y + g->mlx.ray.plane.y
	* g->mlx.ray.camera;
	g->mlx.ray.map.x = (int)g->mlx.player.pos.x;
	g->mlx.ray.map.y = (int)g->mlx.player.pos.y;
	g->mlx.ray.delta_dist.x = fabs(1 / g->mlx.ray.ray_dir.x);
	g->mlx.ray.delta_dist.y = fabs(1 / g->mlx.ray.ray_dir.y);
}

static void	s_side_dist(t_g *g)
{
	if (g->mlx.ray.ray_dir.x < 0)
	{
		g->mlx.ray.step.x = -1;
		g->mlx.ray.side_dist.x = (g->mlx.player.pos.x - g->mlx.ray.map.x)
		* g->mlx.ray.delta_dist.x;
	}
	else
	{
		g->mlx.ray.step.x = 1;
		g->mlx.ray.side_dist.x = (g->mlx.ray.map.x + 1.0 - g->mlx.player.pos.x)
		* g->mlx.ray.delta_dist.x;
	}
	if (g->mlx.ray.ray_dir.y < 0)
	{
		g->mlx.ray.step.y = -1;
		g->mlx.ray.side_dist.y = (g->mlx.player.pos.y - g->mlx.ray.map.y)
		* g->mlx.ray.delta_dist.y;
	}
	else
	{
		g->mlx.ray.step.y = 1;
		g->mlx.ray.side_dist.y = (g->mlx.ray.map.y + 1.0 - g->mlx.player.pos.y)
		* g->mlx.ray.delta_dist.y;
	}
}

static void	s_dda(t_g *g)
{
	int		hit;

	hit = 0;
	while (!hit)
	{
		if (g->mlx.ray.side_dist.x < g->mlx.ray.side_dist.y)
		{
			g->mlx.ray.side_dist.x += g->mlx.ray.delta_dist.x;
			g->mlx.ray.map.x += g->mlx.ray.step.x;
			g->mlx.ray.side = 0;
			g->mlx.ray.pole = g->mlx.ray.step.x == 1 ? 2 : 3;
		}
		else
		{
			g->mlx.ray.side_dist.y += g->mlx.ray.delta_dist.y;
			g->mlx.ray.map.y += g->mlx.ray.step.y;
			g->mlx.ray.side = 1;
			g->mlx.ray.pole = g->mlx.ray.step.y == 1 ? 1 : 0;
		}
		if (g->parse.map[g->mlx.ray.map.y][g->mlx.ray.map.x] == '1')
			hit = 1;
	}
}

static void	s_draw(t_g *g, int i)
{
	if (g->mlx.ray.side == 0)
		g->mlx.ray.perp_wall_dist = (g->mlx.ray.map.x - g->mlx.player.pos.x
		+ (1 - g->mlx.ray.step.x) / 2) / g->mlx.ray.ray_dir.x;
	else
		g->mlx.ray.perp_wall_dist = (g->mlx.ray.map.y - g->mlx.player.pos.y
		+ (1 - g->mlx.ray.step.y) / 2) / g->mlx.ray.ray_dir.y;
	g->mlx.ray.line_height = (int)(g->parse.size.h / g->mlx.ray.perp_wall_dist);
	g->mlx.ray.draw_start = -g->mlx.ray.line_height / 2 + g->parse.size.h / 2;
	if (g->mlx.ray.draw_start < 0)
		g->mlx.ray.draw_start = 0;
	g->mlx.ray.draw_end = g->mlx.ray.line_height / 2 + g->parse.size.h / 2;
	if (g->mlx.ray.draw_end >= g->parse.size.h)
		g->mlx.ray.draw_end = g->parse.size.h - 1;
	g->mlx.ray.z_buffer[i] = g->mlx.ray.perp_wall_dist;
	s_get_texture_pos(g, i, g->mlx.ray.pole);
}

int			s_raycast(t_g *g)
{
	int		i;

	i = 0;
	while (i < g->parse.size.w)
	{
		s_init(g, i);
		s_side_dist(g);
		s_dda(g);
		s_draw(g, i);
		i++;
	}
	s_draw_sprites(g);
	if (g->mlx.save)
	{
		s_bmp(g);
		s_free(g);
		exit(EXIT_SUCCESS);
	}
	mlx_put_image_to_window(g->mlx.ptr, g->mlx.win, g->mlx.img.ptr, 0, 0);
	s_destroy_image(g);
	return (1);
}
