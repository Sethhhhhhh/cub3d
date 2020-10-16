/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:53:03 by yviavant          #+#    #+#             */
/*   Updated: 2020/10/13 11:53:04 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	s_error(t_g *g, char *error)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(error, 1);
	s_free(g);
	exit(EXIT_FAILURE);
}

void	s_check_resolution(t_g *g)
{
	t_size	size;

	size.w = 0;
	size.h = 0;
	mlx_get_screen_size(g->mlx.ptr, &(size.w), &(size.h));
	if (g->parse.size.w > size.w)
		g->parse.size.w = size.w;
	if (g->parse.size.h > size.h)
		g->parse.size.h = size.h;
	if (g->parse.size.w <= 0 || g->parse.size.h <= 0)
		s_error(g, "	Resolution: Your with or height less than 0.\n");
}
