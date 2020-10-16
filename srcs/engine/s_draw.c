/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_draw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:47:27 by yviavant          #+#    #+#             */
/*   Updated: 2020/10/12 17:53:27 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void		s_draw_pixel(t_g *g, int x, int y, int color)
{
	g->mlx.img.data[y * (g->mlx.img.size_line / 4) + x] = color;
}

static void	s_get_start_end_pos(t_g *g, int sprite_id)
{
	g->mlx.sprites[sprite_id].draw_start.y = -g->mlx.sprites[sprite_id].size.h
	/ 2 + g->parse.size.h / 2;
	if (g->mlx.sprites[sprite_id].draw_start.y < 0)
		g->mlx.sprites[sprite_id].draw_start.y = 0;
	g->mlx.sprites[sprite_id].draw_end.y = g->mlx.sprites[sprite_id].size.h
	/ 2 + g->parse.size.h / 2;
	if (g->mlx.sprites[sprite_id].draw_end.y >= g->parse.size.h)
		g->mlx.sprites[sprite_id].draw_end.y = g->parse.size.h - 1;
	g->mlx.sprites[sprite_id].size.w = abs((int)(g->parse.size.h
	/ (g->mlx.sprites[sprite_id].transform.y)));
	g->mlx.sprites[sprite_id].draw_start.x = -g->mlx.sprites[sprite_id].size.w
	/ 2 + g->mlx.sprites[sprite_id].screen;
	if (g->mlx.sprites[sprite_id].draw_start.x < 0)
		g->mlx.sprites[sprite_id].draw_start.x = 0;
	g->mlx.sprites[sprite_id].draw_end.x = g->mlx.sprites[sprite_id].size.w
	/ 2 + g->mlx.sprites[sprite_id].screen;
	if (g->mlx.sprites[sprite_id].draw_end.x >= g->parse.size.w)
		g->mlx.sprites[sprite_id].draw_end.x = g->parse.size.w - 1;
}

void		s_get_screen_sprite_pos(t_g *g, int sprite_id)
{
	double	x;
	double	y;

	x = g->mlx.sprites[sprite_id].pos.x - g->mlx.player.pos.x + .5;
	y = g->mlx.sprites[sprite_id].pos.y - g->mlx.player.pos.y + .5;
	g->mlx.sprites[sprite_id].inv_det = 1.0 / (g->mlx.ray.plane.x
	* g->mlx.ray.dir.y - g->mlx.ray.dir.x * g->mlx.ray.plane.y);
	g->mlx.sprites[sprite_id].transform.x = g->mlx.sprites[sprite_id].inv_det
	* (g->mlx.ray.dir.y * x - g->mlx.ray.dir.x * y);
	g->mlx.sprites[sprite_id].transform.y = g->mlx.sprites[sprite_id].inv_det
	* (-g->mlx.ray.plane.y * x + g->mlx.ray.plane.x * y);
	g->mlx.sprites[sprite_id].screen = (int)((g->parse.size.w / 2) * (1
	+ g->mlx.sprites[sprite_id].transform.x
	/ g->mlx.sprites[sprite_id].transform.y));
	g->mlx.sprites[sprite_id].size.h = abs((int)(g->parse.size.h
	/ (g->mlx.sprites[sprite_id].transform.y)));
	s_get_start_end_pos(g, sprite_id);
}

void		s_draw_sprite(t_g *g, int sprite_id, int i)
{
	int j;

	j = g->mlx.sprites[sprite_id].draw_start.y - 1;
	while (++j < g->mlx.sprites[sprite_id].draw_end.y)
	{
		g->mlx.sprites[sprite_id].texture.y = (((j * 256
		- g->parse.size.h * 128 + g->mlx.sprites[sprite_id].size.h
		* 128) * g->mlx.texture[4].height)
		/ g->mlx.sprites[sprite_id].size.h) / 256;
		g->mlx.sprites[sprite_id].color =
		g->mlx.texture[4].data[g->mlx.sprites[sprite_id].texture.y
		* 64 + g->mlx.sprites[sprite_id].texture.x];
		if (g->mlx.sprites[sprite_id].color != 0)
			s_draw_pixel(g, i, j, g->mlx.sprites[sprite_id].color);
	}
}
