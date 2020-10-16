/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_bmp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:46:40 by yviavant          #+#    #+#             */
/*   Updated: 2020/10/12 13:46:42 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	s_image(t_g *g, t_bmp *bmp)
{
	int x;
	int y;

	y = g->parse.size.h - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < g->parse.size.w)
		{
			bmp->color = g->mlx.img.data[x + (g->mlx.img.size_line / 4) * y];
			write(bmp->fd, &bmp->color, 4);
			x++;
		}
		y--;
	}
}

static void	s_encode(char *encode, int value)
{
	encode[0] = (unsigned char)(value);
	encode[1] = (unsigned char)(value >> 8);
	encode[2] = (unsigned char)(value >> 16);
	encode[3] = (unsigned char)(value >> 24);
}

static void	s_header(t_g *g, t_bmp *bmp)
{
	if (!(bmp->header = (char *)ft_calloc(sizeof(char), 54)))
		s_error(g, "    Bitmap: the mallloc failed impossible to make \
	the header [bmp->header].\n");
	bmp->header[0] = 'B';
	bmp->header[1] = 'M';
	s_encode(&bmp->header[2], 54 + 4 * g->parse.size.w * g->parse.size.h);
	bmp->header[10] = 54;
	bmp->header[14] = 40;
	s_encode(&bmp->header[18], g->parse.size.w);
	s_encode(&bmp->header[22], g->parse.size.h);
	bmp->header[26] = 1;
	bmp->header[28] = g->mlx.img.bits;
	write(bmp->fd, bmp->header, 54);
}

void		s_bmp(t_g *g)
{
	t_bmp	bmp;

	if (!(bmp.fd = open("image.bmp", O_CREAT | O_WRONLY, S_IRWXU)))
		s_error(g, "    Bitmap: Unable to create the image.bmp file \
	[bmp.fd].\n");
	s_header(g, &bmp);
	s_image(g, &bmp);
	close(bmp.fd);
}
