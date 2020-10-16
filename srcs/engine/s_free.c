/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:53:25 by yviavant          #+#    #+#             */
/*   Updated: 2020/10/13 11:53:34 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	s_free_map(t_g *g)
{
	int		i;

	i = 0;
	if (g->parse.map)
	{
		while (i < g->parse.size_grid_y)
		{
			if (g->parse.map[i] != NULL)
				free(g->parse.map[i]);
			i++;
		}
	}
	free(g->parse.map);
}

static void	s_free_window(t_g *g)
{
	if (g->mlx.win != NULL)
		mlx_destroy_window(g->mlx.ptr, g->mlx.win);
}

static void	s_free_texture(t_g *g, int texture_id)
{
	if (g->mlx.texture[texture_id].ptr)
		mlx_destroy_image(g->mlx.ptr, g->mlx.texture[texture_id].ptr);
}

void		s_free(t_g *g)
{
	if (g->mlx.ray.z_buffer != NULL)
		free(g->mlx.ray.z_buffer);
	if (g->parse.map)
		s_free_map(g);
	s_free_texture(g, 0);
	s_free_texture(g, 1);
	s_free_texture(g, 2);
	s_free_texture(g, 3);
	s_free_texture(g, 4);
	if (g->parse.north)
		free(g->parse.north);
	if (g->parse.south)
		free(g->parse.south);
	if (g->parse.west)
		free(g->parse.west);
	if (g->parse.east)
		free(g->parse.east);
	if (g->parse.sprite)
		free(g->parse.sprite);
	if (g->mlx.img.ptr)
		mlx_destroy_image(g->mlx.ptr, g->mlx.img.ptr);
	if (g->mlx.sprites)
		free(g->mlx.sprites);
	s_free_window(g);
}
