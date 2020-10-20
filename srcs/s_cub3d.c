/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_cub3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 14:13:44 by yviavant          #+#    #+#             */
/*   Updated: 2020/10/13 14:13:51 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int				s_is_map_parsing(t_g *g)
{
	if (!g->parse.north || !g->parse.south || !g->parse.east
	|| !g->parse.west || !g->parse.sprite || g->parse.floor == -1
	|| g->parse.ceiling == -1 || (g->parse.size.w == -1)
	|| (g->parse.size.h == -1))
		s_error(g, "	Parsing: bad position of the map file\
	or invalid input.\n");
	return (1);
}

static void		s_init(t_g *g)
{
	g->mlx.save = 0;
	g->parse.lcount = 0;
	g->mlx.texture[0].ptr = NULL;
	g->mlx.texture[1].ptr = NULL;
	g->mlx.texture[2].ptr = NULL;
	g->mlx.texture[3].ptr = NULL;
	g->mlx.texture[4].ptr = NULL;
	g->parse.north = NULL;
	g->parse.south = NULL;
	g->parse.west = NULL;
	g->parse.east = NULL;
	g->parse.sprite = NULL;
	g->mlx.img.ptr = NULL;
	g->mlx.img.data = NULL;
	g->mlx.win = NULL;
	g->mlx.sprites = NULL;
	g->parse.map = NULL;
	g->mlx.ray.z_buffer = NULL;
	g->parse.floor = -1;
	g->parse.ceiling = -1;
	g->parse.size.w = -1;
	g->parse.size.h = -1;
}

static int		s_check_map_path(char *path)
{
	int	len;
	int	fd;

	fd = -1;
	if (!path)
		return (-1);
	len = ft_strlen(path);
	if (path[len - 1] != 'b' && path[len - 2] != 'u'
	&& path[len - 3] != 'c' && path[len - 4] != '.')
		return (-1);
	if ((fd = open(path, O_RDONLY)) <= 0)
		return (-1);
	return (fd);
}

int				main(int ac, char **av)
{
	t_g	g;
	int	fd;

	s_init(&g);
	if (ac < 2)
		s_error(&g, "	Main: Arguments are missing.\n	[Usage]:\
	./cub3d <map.cub> [--save]\n");
	else if (ac > 3)
		s_error(&g, "	Main: Too many arguments.\n	[Usage]:\
	./cub3d <map.cub> [--save]\n");
	if ((fd = s_check_map_path(av[1])) == -1)
		s_error(&g, "	Main: Unable to open the file sent as the first\
	argument.\n	[Usage]: ./cub3d <map.cub> [--save]\n");
	if (ac == 3)
	{
		if (!ft_strcmp(av[2], "--save"))
			g.mlx.save = 1;
		else
			s_error(&g, "	Main: The second argument is wrong.\n	[Usage]:\
		./cub3d <map.cub> [--save]\n");
	}
	s_parse(&g, fd);
	if (!s_init_image(&g))
		return (0);
	return (1);
}
