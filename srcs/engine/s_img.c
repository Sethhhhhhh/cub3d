/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_img.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:59:47 by yviavant          #+#    #+#             */
/*   Updated: 2020/10/13 11:59:49 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	s_setup(t_g *g)
{
	g->mlx.player.forward = 0;
	g->mlx.player.back = 0;
	g->mlx.player.r_left = 0;
	g->mlx.player.r_right = 0;
	if (g->parse.size_grid_y == 0)
		s_error(g, "	Parsing: unknow map.\n");
	g->parse.size_grid_y--;
	if (g->parse.floor == -1 || g->parse.ceiling == -1)
		s_error(g, "	Parsing: the color is not correct.\n	[Usage]:\
		r[0-255], g[0-255], b[0-255]\n");
	s_get_path_to_set(g);
	g->mlx.player.speed = 0.1;
	g->mlx.player.r_speed = 0.1;
	if (!s_get_start_pos(g))
		s_error(g, "	Parsing: the position of the player is unknown.\n");
	s_get_sprites(g);
}

static int	s_loop(t_g *g)
{
	s_move_and_rotate(g);
	s_raycast(g);
	return (0);
}

void		s_destroy_image(t_g *g)
{
	mlx_destroy_image(g->mlx.ptr, g->mlx.img.ptr);
	g->mlx.img.ptr = NULL;
	if (!(g->mlx.img.ptr = mlx_new_image(g->mlx.ptr,
	g->parse.size.w, g->parse.size.h)))
		s_error(g, "	Mlx: the malloc failed impossible to create\
	an image [g->mlx.img.ptr].\n");
	if (!(g->mlx.img.data = (int *)mlx_get_data_addr(g->mlx.img.ptr,
	&(g->mlx.img.bits), &(g->mlx.img.size_line), &(g->mlx.img.endian))))
		s_error(g, "	Mlx: the malloc has failed unable to access the\
	image data [g->mlx.img.data].\n");
}

int			s_close(t_g *g)
{
	s_free(g);
	exit(EXIT_SUCCESS);
	return (1);
}

int			s_init_image(t_g *g)
{
	g->mlx.ptr = mlx_init();
	s_check_resolution(g);
	if (!(g->mlx.win = mlx_new_window(g->mlx.ptr, g->parse.size.w,
	g->parse.size.h, "cub3d")))
		s_error(g, "	Mlx: the malloc failed impossible to create\
	the window [g->mlx.win].\n");
	if (!(g->mlx.img.ptr = mlx_new_image(g->mlx.ptr, g->parse.size.w,
	g->parse.size.h)))
		s_error(g, "	Mlx: the malloc failed impossible to create an\
	image [g->mlx.img.ptr].\n");
	if (!(g->mlx.img.data = (int *)mlx_get_data_addr(g->mlx.img.ptr,
	&(g->mlx.img.bits), &(g->mlx.img.size_line), &(g->mlx.img.endian))))
		s_error(g, "	Mlx: the malloc has failed unable to access the\
	image data [g->mlx.img.data].\n");
	if (!(g->mlx.ray.z_buffer = (double *)malloc(sizeof(double)
	* g->parse.size.w)))
		s_error(g, "	Raycasting: the malloc has failed [z_buffer].\n");
	s_setup(g);
	mlx_hook(g->mlx.win, 2, 1L<<0, s_keypress, g);
	mlx_hook(g->mlx.win, 3, 1L<<1, s_keyrelease, g);
	mlx_hook(g->mlx.win, 17, 0, s_close, g);
	mlx_loop_hook(g->mlx.ptr, s_loop, g);
	mlx_loop(g->mlx.ptr);
	return (1);
}
