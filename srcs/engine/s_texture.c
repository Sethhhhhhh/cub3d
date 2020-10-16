/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_texture.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 12:14:57 by yviavant          #+#    #+#             */
/*   Updated: 2020/10/13 12:15:01 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	s_set_texture(char *path, t_mlx *mlx, int index)
{
	if (!(mlx->texture[index].ptr = mlx_xpm_file_to_image(
		mlx->ptr,
		(char *)path,
		&(mlx->texture[index].width),
		&(mlx->texture[index].height))))
		return (0);
	mlx->texture[index].data = (int *)mlx_get_data_addr(
		mlx->texture[index].ptr,
		&mlx->texture[index].bits,
		&mlx->texture[index].size_line,
		&mlx->texture[index].endian);
	return (1);
}

void		s_get_path_to_set(t_g *g)
{
	if (!(s_set_texture(g->parse.north, &g->mlx, 0)))
		s_error(g, "	Texture: path error on north texture.\n	[Usage]:\
		<yourPath/east>.xpm\n");
	if (!(s_set_texture(g->parse.south, &g->mlx, 1)))
		s_error(g, "	Texture: path error on south texture.\n	[Usage]:\
		<yourPath/east>.xpm\n");
	if (!(s_set_texture(g->parse.west, &g->mlx, 2)))
		s_error(g, "	Texture: path error on west texture.\n	[Usage]:\
		<yourPath/east>.xpm\n");
	if (!(s_set_texture(g->parse.east, &g->mlx, 3)))
		s_error(g, "	Texture: path error on east texture.\n	[Usage]:\
		<yourPath/east>.xpm\n");
	if (!(s_set_texture(g->parse.sprite, &g->mlx, 4)))
		s_error(g, "	Texture: path error on sprite texture.\n	[Usage]:\
		<yourPath/east>.xpm\n");
}

static void	s_draw_texture(t_g *g, int col, int texture, int tex_x)
{
	double	tex_pos;
	double	step;
	int		i;

	i = -1;
	step = 1.0 * g->mlx.texture[texture].height / g->mlx.ray.line_height;
	tex_pos = (g->mlx.ray.draw_start - g->parse.size.h / 2
	+ g->mlx.ray.line_height / 2) * step;
	while (++i < g->parse.size.h)
	{
		if (i >= g->mlx.ray.draw_start && i <= g->mlx.ray.draw_end)
		{
			s_draw_pixel(g, col, i, g->mlx.texture[texture].data[(int)tex_pos
			* (g->mlx.texture[texture].size_line / 4) + tex_x]);
			tex_pos += step;
		}
		else if (i < g->parse.size.h / 2)
			s_draw_pixel(g, col, i, g->parse.ceiling);
		else
			s_draw_pixel(g, col, i, g->parse.floor);
	}
}

void		s_get_texture_pos(t_g *g, int col, int texture)
{
	double	wall_x;
	int		i;
	int		tex_x;

	wall_x = g->mlx.ray.side == 0 ? g->mlx.player.pos.y +
	g->mlx.ray.perp_wall_dist * g->mlx.ray.ray_dir.y :
	g->mlx.player.pos.x + g->mlx.ray.perp_wall_dist
	* g->mlx.ray.ray_dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)g->mlx.texture[texture].width);
	if (g->mlx.ray.side == 0 && g->mlx.ray.ray_dir.x > 0)
		tex_x = g->mlx.texture[texture].width - tex_x - 1.0;
	if (g->mlx.ray.side == 1 && g->mlx.ray.ray_dir.y < 0)
		tex_x = g->mlx.texture[texture].width - tex_x - 1.0;
	s_draw_texture(g, col, texture, tex_x);
}
