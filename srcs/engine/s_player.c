/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_player.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 12:07:01 by yviavant          #+#    #+#             */
/*   Updated: 2020/10/13 12:07:03 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	s_set_plane(t_g *g, char d)
{
	if (d == 'N')
	{
		g->mlx.ray.plane.x = 0.66;
		g->mlx.ray.plane.y = 0;
	}
	else if (d == 'S')
	{
		g->mlx.ray.plane.x = -0.66;
		g->mlx.ray.plane.y = 0;
	}
	else if (d == 'W')
	{
		g->mlx.ray.plane.x = 0;
		g->mlx.ray.plane.y = -0.66;
	}
	else if (d == 'E')
	{
		g->mlx.ray.plane.x = 0;
		g->mlx.ray.plane.y = 0.66;
	}
}

static void	s_set_dir(t_g *g, char d)
{
	if (d == 'N')
	{
		g->mlx.ray.dir.x = 0;
		g->mlx.ray.dir.y = -1;
	}
	else if (d == 'S')
	{
		g->mlx.ray.dir.x = 0;
		g->mlx.ray.dir.y = 1;
	}
	else if (d == 'W')
	{
		g->mlx.ray.dir.x = -1;
		g->mlx.ray.dir.y = 0;
	}
	else if (d == 'E')
	{
		g->mlx.ray.dir.x = 1;
		g->mlx.ray.dir.y = 0;
	}
	s_set_plane(g, d);
}

int			s_get_start_pos(t_g *g)
{
	int		i;
	int		j;
	int		has_player;

	i = -1;
	has_player = 0;
	while (++i < g->parse.size_grid_y)
	{
		j = -1;
		while (g->parse.map[i][++j])
			if (ft_strchr("NSWE", g->parse.map[i][j]))
			{
				g->mlx.player.pos.x = j + 0.5;
				g->mlx.player.pos.y = i + 0.5;
				s_set_dir(g, g->parse.map[i][j]);
				g->parse.map[i][j] = '0';
				has_player++;
			}
	}
	if (has_player > 1)
		s_error(g, "	Parsing: There are too many players on the map.\n");
	else if (has_player <= 0)
		return (0);
	return (1);
}

void		s_move_and_rotate(t_g *g)
{
	s_move(g);
	s_rotate_left(g);
	s_rotate_right(g);
}
