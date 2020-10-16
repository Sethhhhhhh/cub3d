/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_sprite.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 12:10:04 by yviavant          #+#    #+#             */
/*   Updated: 2020/10/13 12:10:05 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void		s_get_sprite_dist(t_g *g)
{
	int	sprite_id;

	sprite_id = 0;
	while (sprite_id < g->parse.count_sprite)
	{
		g->mlx.sprites[sprite_id].dist = sqrt(pow(g->mlx.player.pos.x
		- g->mlx.sprites[sprite_id].pos.x, 2) + pow(g->mlx.player.pos.y
		- g->mlx.sprites[sprite_id].pos.y, 2));
		sprite_id++;
	}
}

void		s_sort_sprites(t_g *g)
{
	int			i;
	t_sprite	tmp;

	s_get_sprite_dist(g);
	i = 0;
	while (i < g->parse.count_sprite - 1)
	{
		if (g->mlx.sprites[i].dist < g->mlx.sprites[i + 1].dist)
		{
			tmp = g->mlx.sprites[i];
			g->mlx.sprites[i] = g->mlx.sprites[i + 1];
			g->mlx.sprites[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

static void	s_count_sprite(t_parse *parse)
{
	int	y;
	int	x;

	parse->count_sprite = 0;
	y = 0;
	while (y < parse->size_grid_y)
	{
		x = 0;
		while (parse->map[y][x])
		{
			if (parse->map[y][x] == '2')
				(parse->count_sprite)++;
			x++;
		}
		y++;
	}
}

void		s_get_sprites(t_g *g)
{
	int	y;
	int	x;
	int	sprite_id;

	s_count_sprite(&g->parse);
	if (!(g->mlx.sprites = (t_sprite *)malloc(sizeof(t_sprite)
	* g->parse.count_sprite)))
		s_error(g, "    Sprites: the malloc failed impossible to create a\
		sprite table [g->mlx.sprites].\n");
	y = 0;
	sprite_id = 0;
	while (y < g->parse.size_grid_y)
	{
		x = -1;
		while (g->parse.map[y][++x])
		{
			if (g->parse.map[y][x] == '2')
			{
				g->mlx.sprites[sprite_id].pos.x = x;
				g->mlx.sprites[sprite_id].pos.y = y;
				sprite_id++;
			}
		}
		y++;
	}
}

void		s_draw_sprites(t_g *g)
{
	int	i;
	int	sprite_id;

	sprite_id = 0;
	s_sort_sprites(g);
	while (sprite_id < g->parse.count_sprite)
	{
		s_get_screen_sprite_pos(g, sprite_id);
		i = g->mlx.sprites[sprite_id].draw_start.x - 1;
		while (++i < g->mlx.sprites[sprite_id].draw_end.x)
		{
			g->mlx.sprites[sprite_id].texture.x = (int)(256 *
			(i - (-g->mlx.sprites[sprite_id].size.w / 2
			+ g->mlx.sprites[sprite_id].screen)) * g->mlx.texture[4].width
			/ g->mlx.sprites[sprite_id].size.w) / 256;
			if (g->mlx.sprites[sprite_id].transform.y > 0 && i > 0
			&& i < g->parse.size.w && g->mlx.sprites[sprite_id].transform.y
			< g->mlx.ray.z_buffer[i])
			{
				s_draw_sprite(g, sprite_id, i);
			}
		}
		sprite_id++;
	}
}
